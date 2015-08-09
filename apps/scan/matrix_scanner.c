/****************************************************************************
 *
 *  Keyboard matrix scanner
 *
 ***************************************************************************/

#include <string.h>
#include "apps/scan/matrix_scanner.h"


//---------------------------------------------------------------------------
// Static function prototypes.

static void rkas_read_matrix( RkASMatrixScanner *, uint8_t, uint8_t );


//---------------------------------------------------------------------------

/**
 * @brief Initialize the matrix scanner.
 *
 * @param[in] self the scanner to initialize
 */
void rkas_init( RkASMatrixScanner * self ) {

  // To use PORTF, disable JTAG by writing JTD bit twice within four cycles:
  /*MCUCR |= (1<<JTD);*/
  /*MCUCR |= (1<<JTD);*/


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
 * @brief Scan the matrix once.
 *
 * @param[in] self the keyboard matrix scanner
 * @param[in] num_rows the number of rows in the matrix
 * @param[in] num_cols the number of cols in the matrix
 */
static void rkas_read_matrix(
  RkASMatrixScanner * self,
  uint8_t num_rows,
  uint8_t num_cols
) {

  uint8_t bytes_per_row = RKAS_MATRIX_BYTES_PER_ROW( num_cols );
  uint8_t offset = 0;

  for ( uint8_t row = 0; row < num_rows; row++ ) {

    self->scan_row(
      self, row,
      &(*self->state.latest)[ offset ]
    );

    offset += bytes_per_row;
  }
}


/**
 * @brief Scan the matrix.
 *
 * @param[in] self the keyboard matrix scanner
 */
void rkas_scan( RkASMatrixScanner * self ) {

  uint8_t num_rows, num_cols;

  rkas_get_geometry(
    self->matrix, self->matrix_in_progmem,
    &num_rows, &num_cols
  );

  // Read the current state of the matrix:
  rkas_read_matrix( self, num_rows, num_cols );

  // Check for changes:
  uint16_t state_size = RKAS_MATRIX_STATE_SIZE( num_rows, num_cols );
  if (
    memcmp( *self->state.bouncing, *self->state.latest, state_size )
  ) {
    // Bounce detected.

    // Record time of bounce:
    chSysLock();
    self->last_bounce_time = chVTGetSystemTimeX();
    chSysUnlock();

    // Record what bounced:
    memcpy( *self->state.bouncing, *self->state.latest, state_size );

  } else {
    // Current state is the same as last bounce.

    // Check if settle time has elapsed:
    chSysLock();
    systime_t elapsed = chVTTimeElapsedSinceX( self->last_bounce_time );
    chSysUnlock();

    if ( elapsed >= MS2ST( RKAS_DEBOUNCE_MS ) ) {
      // Matrix has been stable long enough.

      // See if anything changed from last reported state:
      if (
        memcmp( *self->state.reported, *self->state.latest, state_size )
      ) {
        // Generate events.

        // Record matrix state as reported:
        memcpy( *self->state.reported, *self->state.latest, state_size );
      }
    }
  }
}


//===========================================================================

/* vi: set et sts=2 sw=2 ts=2: */
