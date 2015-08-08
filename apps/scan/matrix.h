/****************************************************************************
 *
 *  Keyboard matrix interface
 *
 ***************************************************************************/
#if !defined(__RK_AS_MATRIX__)
#define __RK_AS_MATRIX__

#include "apps/scan/matrix_layout.h"

/***************************************************************************/

/* Keyboard state array elements: */
#define RK_AS_MATRIX_STATE_REPORTED 0
#define RK_AS_MATRIX_STATE_LATEST 1
#define RK_AS_MATRIX_STATE_BOUNCING 2


/**
 * @brief   Keyboard matrix data structure.
 */
typedef struct rk_as_matrix {
  /**
   * @brief Keyboard matrix layout.
   */
  const RkASMatrixLayout    *layout;
  /**
   * @brief Arrays of matrix state data.
   */
  struct {
    uint8_t (*reported)[];
    uint8_t (*latest)[];
    uint8_t (*bouncing)[];
  } state;
//  uint8_t                   (*state[3])[];
  /**
   * @brief Whether the layout data are stored in PROGMEM.
   */
  bool layout_in_progmem;
  /* End of the mandatory fields.*/
} RkASMatrix;


// From:
// http://stackoverflow.com/questions/1082192/how-to-generate-random-variable-names-in-c-using-macros/17624752#17624752
//
// This is some crazy magic that helps produce __BASE__247
// Vanilla interpolation of __BASE__##__LINE__ would produce __BASE____LINE__
// I still can't figure out why it works, but it has to do with macro resolution ordering
#define PP_CAT(a, b) PP_CAT_I(a, b)
#define PP_CAT_I(a, b) PP_CAT_II(~, a ## b)
#define PP_CAT_II(p, res) res
#define UNIQUE_NAME(base) PP_CAT(base, __COUNTER__)

// Use to create a matrix structure on the stack:
#define DEFINE_MATRIX( name, layout_, layout_in_progmem_ ) \
  DEFINE_MATRIX_2( \
    name, \
    (layout_), \
    (layout_in_progmem_), \
    UNIQUE_NAME( rkas_matrix_state_reported ), \
    UNIQUE_NAME( rkas_matrix_state_latest ), \
    UNIQUE_NAME( rkas_matrix_state_bouncing ), \
    UNIQUE_NAME( rkas_matrix_state_size ) \
  )

#define DEFINE_MATRIX_2( name, layout_, layout_in_progmem_, state_reported, state_latest, state_bouncing, state_size ) \
  uint16_t state_size = rkas_get_state_size( &layout_, layout_in_progmem_ ); \
  uint8_t state_reported[ state_size ]; \
  uint8_t state_latest[ state_size ]; \
  uint8_t state_bouncing[ state_size ]; \
\
  RkASMatrix name = { \
    .layout = &layout_, \
    .state = { \
      .reported = &state_reported, \
      .latest = &state_latest, \
      .bouncing = &state_bouncing \
    }, \
    .layout_in_progmem = layout_in_progmem_ \
  }


/***************************************************************************/
// Static prototypes:

void rkas_init( RkASMatrix * );


/***************************************************************************/

#endif

/* vi: set et sts=2 sw=2 ts=2: */
