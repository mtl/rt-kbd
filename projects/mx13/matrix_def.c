/****************************************************************************
 *
 *  Keyboard matrix definition
 *
 ***************************************************************************/

//#include <avr/interrupt.h>
#include <avr/pgmspace.h>
//#include <avr/power.h>
//#include <avr/wdt.h>
//#include "hal.h"
//#include "nil.h"

//#include "ch.h"
#include "hal.h"
#include "pal.h"
#include "pal_lld.h"
//#include "test.h"

#include "matrix_def.h"
#include "apps/scan/scanner_a.h"

/**
 * @brief RAM-based keyboard matrix configuration.
 */
const RkASMatrixLayout matrix_layout = {
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
 * @brief Progmem keyboard matrix layout.
 */
const RkASMatrixLayout matrix_layout_P PROGMEM = {
  .num_rows = KBD_MATRIX_NUM_ROWS,
  .num_cols = KBD_MATRIX_NUM_COLS,
//  .row_pins = &(IOBus[]){ ROW_DEFS },
  .row_pins = row_pins,
  .col_pins = col_pins,
};


/***************************************************************************/

/* vi: set et sts=2 sw=2 ts=2: */
