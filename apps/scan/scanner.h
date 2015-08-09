/****************************************************************************
 *
 *  Keyboard matrix interface
 *
 ***************************************************************************/
#if !defined(__RK_AS_SCANNER__)
#define __RK_AS_SCANNER__

//---------------------------------------------------------------------------
// Includes.

#include "apps/scan/matrix.h"


//---------------------------------------------------------------------------
// Macros.

/**
 * @brief   Static working area allocation for keyboard matrix scanner.
 * @details This macro is used to allocate a static thread working area
 *          for a keyboard matrix scanner.
 *
 * @param[in] scanner   the scanner "class"
 * @param[in] id        the thread identifier
 */
#define RK_AS_SCANNER( scanner, id ) \
  THD_WORKING_AREA( id ## WA, scanner ## WASize )


/**
 * @brief   User threads table entry for keyboard matrix scanner
 * @details This macro is used to emit an entry for the user threads table
 *          to represent a keyboard matrix scanner thread.
 *
 * @param[in] scanner   the scanner "class"
 * @param[in] id        the thread identifier
 * @param[in] name      the thread name (string)
 * @param[in] config    the scanner configuration
 */
#define RK_AS_SCANNER_THD( scanner, id, name, config ) \
  THD_TABLE_ENTRY( id ## WA, name, scanner ## F, config )


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
#define DEFINE_SCANNER( name, matrix_, matrix_in_progmem_ ) \
  DEFINE_SCANNER_2( \
    name, \
    (matrix_), \
    (matrix_in_progmem_), \
    UNIQUE_NAME( rkas_matrix_state_reported ), \
    UNIQUE_NAME( rkas_matrix_state_latest ), \
    UNIQUE_NAME( rkas_matrix_state_bouncing ), \
    UNIQUE_NAME( rkas_matrix_state_size ) \
  )

#define DEFINE_SCANNER_2( name, matrix_, matrix_in_progmem_, state_reported, state_latest, state_bouncing, state_size ) \
  uint16_t state_size = rkas_get_state_size( &matrix_, matrix_in_progmem_ ); \
  uint8_t state_reported[ state_size ]; \
  uint8_t state_latest[ state_size ]; \
  uint8_t state_bouncing[ state_size ]; \
\
  RkASScanner name = { \
    .matrix = &matrix_, \
    .state = { \
      .reported = &state_reported, \
      .latest = &state_latest, \
      .bouncing = &state_bouncing \
    }, \
    .matrix_in_progmem = matrix_in_progmem_ \
  }


//---------------------------------------------------------------------------
// Data structures.

/**
 * @brief   Keyboard matrix scanner data structure.
 */
typedef struct rk_as_scanner {

  /**
   * @brief Keyboard matrix definition.
   */
  const RkASMatrix          *matrix;

  /**
   * @brief Row scan function.
   */
  void (*scan_row)( struct rk_as_scanner*, uint8_t, uint8_t[] );

  /**
   * @brief Arrays of matrix state data.
   */
  struct {
    uint8_t (*reported)[];
    uint8_t (*latest)[];
    uint8_t (*bouncing)[];
  } state;

  /**
   * @brief Whether the matrix definition is stored in progmem.
   */
  bool matrix_in_progmem;

  /* End of the mandatory fields.*/

} RkASScanner;


//---------------------------------------------------------------------------
// Function prototypes.

void rkas_init( RkASScanner *, void (*scan_row)( RkASScanner*, uint8_t, uint8_t[] ) );


//===========================================================================

#endif

/* vi: set et sts=2 sw=2 ts=2: */
