/****************************************************************************
 *
 *  Keyboard matrix definition
 *
 ***************************************************************************/

#include <avr/pgmspace.h>

#include "hal.h"
#include "pal.h"
#include "pal_lld.h"

#include "matrix_def.h"


//---------------------------------------------------------------------------

/**
 * @brief RAM-based keyboard matrix configuration.
 */
const RkASMatrix matrix = {
  .num_rows = KBD_MATRIX_NUM_ROWS,
  .num_cols = KBD_MATRIX_NUM_COLS,
  .row_pins = &(IOBus[]){ ROW_DEFS },
  .col_pins = &(IOBus[]){ COL_DEFS }
};


/**
 * @brief Progmem keyboard matrix rows.
 */
static const IOBus row_pins[] PROGMEM = { ROW_DEFS };


/**
 * @brief Progmem keyboard matrix columns.
 */
static const IOBus col_pins[] PROGMEM = { COL_DEFS };


/**
 * @brief Progmem-based keyboard matrix configuration.
 */
const RkASMatrix matrix_P PROGMEM = {
  .num_rows = KBD_MATRIX_NUM_ROWS,
  .num_cols = KBD_MATRIX_NUM_COLS,
  .row_pins = row_pins,
  .col_pins = col_pins,
};


//===========================================================================

/* vi: set et sts=2 sw=2 ts=2: */
