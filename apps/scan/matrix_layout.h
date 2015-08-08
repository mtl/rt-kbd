/****************************************************************************
 *
 *  Keyboard matrix layout
 *
 ***************************************************************************/
#if !defined(__RK_AS_MATRIX_LAYOUT__)
#define __RK_AS_MATRIX_LAYOUT__

#include "hal.h"
#include "pal.h"

/***************************************************************************/

/**
 * @brief   Keyboard matrix layout data structure.
 */
typedef struct rk_as_matrix_layout {
  /**
   * @brief Number of rows in the matrix.
   */
  uint8_t                   num_rows;
  /**
   * @brief Number of columns in the matrix.
   */
  uint8_t                   num_cols;
  /**
   * @brief Array of row pin descriptors.
   * @note  @p IOBus.mask must have only one bit set.
   */
  IOBus                     (*row_pins)[];
  /**
   * @brief Array of column pin descriptors.
   * @note  @p IOBus.mask must have only one bit set.
   */
  IOBus                     (*col_pins)[];
  /* End of the mandatory fields.*/
} RkASMatrixLayout;


/***************************************************************************/
// Static prototypes:

void rkas_get_layout_geometry( const RkASMatrixLayout *, bool, uint8_t *, uint8_t * );
uint16_t rkas_get_state_size( const RkASMatrixLayout *, bool );
void rkas_load_layout_from_eeprom( RkASMatrixLayout *, const RkASMatrixLayout * );


/***************************************************************************/

#endif

/* vi: set et sts=2 sw=2 ts=2: */
