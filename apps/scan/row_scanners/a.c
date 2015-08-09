/****************************************************************************
 *
 *  Keyboard matrix row scanner A
 *
 ***************************************************************************/

#include <avr/pgmspace.h>
#include <util/delay.h>

#include "nil.h"
#include "hal.h"
#include "pal.h"

#include "apps/scan/row_scanners/a.h"


//---------------------------------------------------------------------------
// Static function prototypes:

static void get_pin( ioportid_t *, uint_fast8_t *, IOBus [], uint8_t, bool );
static void get_pins_address( IOBus (**)[], IOBus (* const *)[], bool );
static void scan_row( RkASMatrixScanner *, uint8_t, uint8_t[] );
static void select_row( RkASMatrixScanner *, uint8_t );
static void unselect_row( RkASMatrixScanner *, uint8_t );


//---------------------------------------------------------------------------

/**
 * @brief   The thread function for a Scanner A thread.
 * @details This function is declared noreturn and its signature has a void
 *          return type.
 *
 * @param[in] arg       unused (type void *)
 */
//THD_FUNCTION( fwIKScannerF, arg ) {
//}






/**
 * @brief Get information about a matrix row or column pin.
 *
 * @param[out] portid the pin's I/O port
 * @param[out] offset the bit position of the pin on the I/O port
 * @param[in] pins the array of matrix pin definitions
 * @param[in] number the row or column number
 * @param[in] use_pgm whether or not to read from progmem
 */
static void get_pin(
    ioportid_t * portid, uint_fast8_t * offset,
    IOBus pins[], uint8_t number, bool use_pgm
) {

  if ( use_pgm ) {

    // Get the pin information from progmem:
    IOBus pin;
    memcpy_P(
      &pin,
      &pins[ number ],
      sizeof( IOBus )
    );

    *portid = pin.portid;
    *offset = pin.offset;

  } else {

    *portid = pins[ number ].portid;
    *offset = pins[ number ].offset;
  }
}


/**
 * @brief Get the address of a pin configuration array.
 *
 * @param[out] dest where to store the array's address
 * @param[in] src where to retrieve the array's address
 * @param[in] use_pgm whether or not to read from progmem
 */
static void get_pins_address(
    IOBus (**dest)[],
    IOBus (* const *src)[],
    bool use_pgm
) {

  if ( use_pgm ) {

    *dest = (IOBus (*)[]) pgm_read_word_near( src );

  } else {

    *dest = *src;
  }
}


/**
 * @brief Initialize the scanner.
 *
 * @param[in] matrix_scanner the keyboard matrix scanner
 */
void rkas_init_a( RkASMatrixScanner * matrix_scanner ) {

  // Tell the matrix scanner how to scan a row:
  matrix_scanner->scan_row = &scan_row;

  // Get matrix geometry:
  uint8_t num_rows, num_cols;
  bool use_pgm = matrix_scanner->matrix_in_progmem;
  const RkASMatrix * matrix = matrix_scanner->matrix;
  rkas_get_geometry( matrix, use_pgm, &num_rows, &num_cols );

  // Initialize rows:
  for ( uint8_t row = 0; row < num_rows; row++ ) {
    unselect_row( matrix_scanner, row );
  }

  // Initialize columns:

  IOBus (*col_pins)[] = NULL;
  get_pins_address( &col_pins, &matrix->col_pins, use_pgm );

  uint_fast8_t offset;
  ioportid_t portid;
  for ( uint8_t col = 0; col < num_cols; col++ ) {

    get_pin( &portid, &offset, *col_pins, col, use_pgm );
    palSetPadMode( portid, offset, PAL_MODE_INPUT_PULLUP );
  }
}


/**
 * @brief   Select a row to be scanned.
 * @details Output low (DDR:1, PORT:0) to select.
 *
 * @param[in] matrix_scanner the keyboard matrix scanner
 * @param[in] row the number of the row to select
 *
 * @notapi
 */
static void select_row( RkASMatrixScanner * matrix_scanner, uint8_t row ) {

  IOBus (*row_pins)[] = NULL;
  bool use_pgm = matrix_scanner->matrix_in_progmem;
  get_pins_address( &row_pins, &matrix_scanner->matrix->row_pins, use_pgm );

  uint_fast8_t offset;
  ioportid_t portid;
  get_pin( &portid, &offset, *row_pins, row, use_pgm );

  palSetPadMode( portid, offset, PAL_MODE_OUTPUT_PUSHPULL );
  palWritePad( portid, offset, PAL_LOW );
}


/**
 * @brief Get a row of matrix column data.
 *
 * @param[in] matrix_scanner the keyboard matrix scanner
 * @param[in] row the number of the row to scan
 * @param[out] columns the column data
 *
 * @note Column 0 is the LSb of @p columns[0].
 * @note Column 8 is the LSb of @p columns[1].  Etc.
 *
 * @return the row of data
 */
static void scan_row( RkASMatrixScanner * matrix_scanner, uint8_t row, uint8_t columns[] ) {

  select_row( matrix_scanner, row );
  _delay_us( 30 );  // Wait for signals to stabilize.

  uint8_t num_rows, num_cols;
  const RkASMatrix * matrix = matrix_scanner->matrix;
  bool use_pgm = matrix_scanner->matrix_in_progmem;
  rkas_get_geometry( matrix, use_pgm, &num_rows, &num_cols );

  IOBus (*col_pins)[] = NULL;
  get_pins_address( &col_pins, &matrix->col_pins, use_pgm );

  uint8_t col_bit = 0;
  uint8_t col_byte = 0;
  uint8_t col_byte_offset = 0;
  uint_fast8_t offset;
  ioportid_t portid;

  for ( uint8_t col = 0; col < num_cols; col++ ) {

    if ( col_bit > 7 ) {
      columns[ col_byte_offset++ ] = col_byte;
      col_bit = 0;
      col_byte = 0;
    }

    get_pin( &portid, &offset, *col_pins, col, use_pgm );
    col_byte |= palReadPad( portid, offset ) << col_bit++;
  }

  unselect_row( matrix_scanner, row );
}


/**
 * @brief   Unselect a row (to initialize or after scanning).
 * @details Hi-Z input (DDR:0, PORT:0) to unselect.
 *
 * @param[in] matrix_scanner the keyboard matrix scanner
 * @param[in] row the number of the row to unselect
 *
 * @notapi
 */
static void unselect_row( RkASMatrixScanner * matrix_scanner, uint8_t row ) {

  IOBus (*row_pins)[] = NULL;
  bool use_pgm = matrix_scanner->matrix_in_progmem;
  get_pins_address( &row_pins, &matrix_scanner->matrix->row_pins, use_pgm );

  uint_fast8_t offset;
  ioportid_t portid;
  get_pin( &portid, &offset, *row_pins, row, use_pgm );

  palSetPadMode( portid, offset, PAL_MODE_INPUT );
}


//===========================================================================

/* vi: set et sts=2 sw=2 ts=2: */
