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
 */
void rkas_init( RkASScanner * self ) {

  uint16_t matrix_state_size = rkas_get_state_size(
    self->matrix, self->matrix_in_progmem
  );

  memset( self->state.reported, 0, matrix_state_size );
  memset( self->state.latest, 0, matrix_state_size );
  memset( self->state.bouncing, 0, matrix_state_size );
}


//===========================================================================

/* vi: set et sts=2 sw=2 ts=2: */
