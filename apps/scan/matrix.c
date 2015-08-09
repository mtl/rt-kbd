/****************************************************************************
 *
 *  Keyboard matrix
 *
 ***************************************************************************/

#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include "apps/scan/matrix.h"


/*-------------------------------------------------------------------------*/

/**
 * @brief Get the matrix geometry.
 *
 * @param[out] num_rows the number of rows in the matrix
 * @param[out] num_cols the number of columns in the matrix
 * @param[in] self the matrix definition
 * @param[in] progmem true if the matrix definition is in progmem (otherwise RAM)
 */
void rkas_get_geometry(
  const RkASMatrix * self,
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
  const RkASMatrix * self,
  bool progmem
) {

  uint8_t num_rows, num_cols;

  rkas_get_geometry( self, progmem, &num_rows, &num_cols );

  /* Pack 8 bits per byte.
   * Add an extra byte for any extra bits.
   */
  return (
    num_rows * ( num_cols / 8 + ( num_cols % 8 ? 1 : 0 ) )
  );
}


/**
 * @brief Load a matrix definition from EEPROM.
 *
 * @param[out] self the RAM location to fill with the matrix definition
 * @param[in] eeprom_address the EEPROM location to read matrix definition from
 */
void rkas_load_from_eeprom(
    RkASMatrix * self,
    const RkASMatrix * eeprom_address
) {

  // Read data from EEPROM:
  eeprom_read_block(
    self,
    eeprom_address,
    sizeof( RkASMatrix )
  );
}


//===========================================================================

/* vi: set et sts=2 sw=2 ts=2: */
