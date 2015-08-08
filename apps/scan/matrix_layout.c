/****************************************************************************
 *
 *  Keyboard matrix interface
 *
 ***************************************************************************/

#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include "apps/scan/matrix_layout.h"


/***************************************************************************/

/**
 * @brief Get the matrix layout geometry.
 *
 * @param[out] num_rows the number of rows in the layout
 * @param[out] num_cols the number of columns in the layout
 * @param[in] self the matrix layout
 * @param[in] progmem true if the layout is in progmem (otherwise RAM)
 */
void rkas_get_layout_geometry(
  const RkASMatrixLayout * self,
  bool progmem,
  uint8_t * num_rows,
  uint8_t * num_cols
) {

  if ( progmem ) {
    *num_rows = pgm_read_byte( &self->num_rows );
    *num_cols = pgm_read_byte( &self->num_cols );
  } else {
    *num_rows = self->num_rows;
    *num_cols = self->num_cols;
  }
}


/**
 * @brief Get the amount of memory required to store the matrix state.
 *
 * @param[in] self the matrix layout
 * @param[in] progmem true if the layout is in progmem (otherwise RAM)
 * @return the number of bytes required to store the matrix state
 */
uint16_t rkas_get_state_size(
  const RkASMatrixLayout * layout,
  bool progmem
) {

  uint8_t num_rows, num_cols;

  rkas_get_layout_geometry( layout, progmem, &num_rows, &num_cols );

  /* Need to keep 3 matrices (reported, latest, bouncing).
   * Pack 8 bits per byte.
   * Add an extra byte for any extra bits.
   */
  return (
    3 * num_rows * ( num_cols / 8 + ( num_cols % 8 ? 1 : 0 ) )
  );
}


/**
 * @brief Load a keyboard matrix layout from EEPROM.
 *
 * @param[out] self the RAM location to fill with the layout data
 * @param[in] eeprom_address the EEPROM location to read layout data from
 */
void rkas_load_layout_from_eeprom(
    RkASMatrixLayout * self,
    const RkASMatrixLayout * eeprom_address
) {

  // Read data from EEPROM:
  eeprom_read_block(
    self,
    eeprom_address,
    sizeof( RkASMatrixLayout )
  );
}


/***************************************************************************/

/* vi: set et sts=2 sw=2 ts=2: */
