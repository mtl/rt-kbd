/****************************************************************************
 *
 *  Keyboard matrix
 *
 ***************************************************************************/
#if !defined(__RK_AS_MATRIX__)
#define __RK_AS_MATRIX__

//---------------------------------------------------------------------------
// Includes.

#include "hal.h"
#include "pal.h"


//---------------------------------------------------------------------------
// Macros.

/* Pack 8 bits per byte.
 * Add an extra byte for any extra bits.
 */
#define RKAS_MATRIX_BYTES_PER_ROW( num_cols ) \
  (num_cols) / 8 + ( (num_cols) % 8 ? 1 : 0 )

#define RKAS_MATRIX_STATE_SIZE( num_rows, num_cols ) \
  (num_rows) * RKAS_MATRIX_BYTES_PER_ROW( (num_cols) )


//---------------------------------------------------------------------------
// Data structures.

/**
 * @brief   Keyboard matrix configuration data structure.
 */
typedef struct rk_as_matrix {
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
} RkASMatrix;


//---------------------------------------------------------------------------
// Function prototypes.

void rkas_get_geometry( const RkASMatrix *, bool, uint8_t *, uint8_t * );
uint16_t rkas_get_state_size( const RkASMatrix *, bool );
void rkas_load_from_eeprom( RkASMatrix *, const RkASMatrix * );


//===========================================================================

#endif

/* vi: set et sts=2 sw=2 ts=2: */
