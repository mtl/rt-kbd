/****************************************************************************
 *
 *  Keyboard matrix row scanner A
 *
 ***************************************************************************/
#if !defined(__RK_AS_ROW_SCANNER_A__)
#define __RK_AS_ROW_SCANNER_A__

//---------------------------------------------------------------------------
// Includes.

#include <stdint.h>
#include "apps/scan/matrix_scanner.h"

//---------------------------------------------------------------------------
// Macros.

/**
 * @brief   The working area size for a scanner A thread.
 */
#define rkASScannerAWASize 128


//---------------------------------------------------------------------------
// Data structures.

/**
 * @brief   Keyboard row scanner A data structure.
 */
//typedef struct rk_as_row_scanner_a {
//
//  /**
//   * @brief Keyboard matrix row scanner (base).
//   */
//  RkASScanner super;
//
//} RkASRowScannerA;



//---------------------------------------------------------------------------
// Function rototypes.

//void rkASScannerAF( void * );

void rkas_init_a( RkASMatrixScanner * );


//===========================================================================

#endif

/* vi: set et sts=2 sw=2 ts=2: */
