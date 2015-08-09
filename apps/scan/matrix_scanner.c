/****************************************************************************
 *
 *  Keyboard matrix scanner
 *
 ***************************************************************************/

#include <string.h>
#include "apps/scan/matrix_scanner.h"


//---------------------------------------------------------------------------

/**
 * @brief Initialize the matrix scanner.
 *
 * @param[in] self the scanner to initialize
 */
void rkas_init( RkASMatrixScanner * self ) {

  // Initialize the matrix state arrays:

  uint16_t matrix_state_size = rkas_get_state_size(
    self->matrix, self->matrix_in_progmem
  );

  memset( self->state.reported, 0, matrix_state_size );
  memset( self->state.latest, 0, matrix_state_size );
  memset( self->state.bouncing, 0, matrix_state_size );
}


/**
 * @brief Print the current matrix state.
 *
 * @param[in] self the keyboard matrix scanner
 */
void rkas_print( RkASMatrixScanner * self ) {
}


/**
 * @brief Scan the matrix.
 *
 * @param[in] self the keyboard matrix scanner
 */
static uint8_t rkas_scan( RkASMatrixScanner * self ) {

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
