/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/
#if !defined(__RK_AS_MATRIX_SCANNER_A__)
#define __RK_AS_MATRIX_SCANNER_A__

//---------------------------------------------------------------------------
// Includes.

#include <stdint.h>
#include "apps/scan/scanner.h"

//---------------------------------------------------------------------------
// Macros.

/**
 * @brief   The working area size for a scanner A thread.
 */
#define rkASScannerAWASize 128


//---------------------------------------------------------------------------
// Data structures.

/**
 * @brief   Keyboard matrix scanner A data structure.
 */
typedef struct rk_as_scanner_a {

  /**
   * @brief Keyboard matrix scanner (base).
   */
  RkASScanner super;

} RkASScannerA;



//---------------------------------------------------------------------------
// Function rototypes.

//void rkASScannerAF( void * );
//void scanner_a( RkASScanner * );

void scan_row( RkASScanner *, uint8_t, uint8_t[] );


//===========================================================================

#endif

/* vi: set et sts=2 sw=2 ts=2: */
