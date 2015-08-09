/****************************************************************************
 *
 *  Keyboard matrix scanner
 *
 ***************************************************************************/

#include <string.h>
#include "apps/scan/scanner.h"


//---------------------------------------------------------------------------

/**
 * @brief Initialize the scanner.
 *
 * @param[in] self the scanner to initialize
 * @param[in] scan_row the row scanning function
 */
void rkas_init(
  RkASScanner * self,
  void (*scan_row)( RkASScanner*, uint8_t, uint8_t[] )
) {
  self->scan_row = scan_row;

  // Initialize the matrix state arrays:

  uint16_t matrix_state_size = rkas_get_state_size(
    self->matrix, self->matrix_in_progmem
  );

  memset( self->state.reported, 0, matrix_state_size );
  memset( self->state.latest, 0, matrix_state_size );
  memset( self->state.bouncing, 0, matrix_state_size );
}


/**
 * @brief Scan the matrix.
 *
 * @param[in] self the keyboard matrix scanner
 */
static uint8_t rkas_scan( RkASScanner * self ) {

  uint8_t num_rows, num_cols;

  rkas_get_geometry(
    self->matrix, self->matrix_in_progmem,
    &num_rows, &num_cols
  );

  for ( uint8_t row = 0; row < num_rows; row++ ) {

//    self->scan_row( self, row, ... );
  }
}


//===========================================================================

/* vi: set et sts=2 sw=2 ts=2: */
