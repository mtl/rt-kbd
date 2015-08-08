/****************************************************************************
 *
 *  Keyboard matrix interface
 *
 ***************************************************************************/

#include "apps/scan/matrix.h"


/***************************************************************************/

/**
 * @brief Initialize the matrix.
 *
 * @param[in] matrix the matrix to initialize
 */
void rkas_init( RkASMatrix * self ) {


  uint8_t num_rows, num_cols;
  rkas_get_layout_geometry(
    self->layout, self->layout_in_progmem,
    &num_rows, &num_cols
  );





}


/***************************************************************************/

/* vi: set et sts=2 sw=2 ts=2: */
