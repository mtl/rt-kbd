/****************************************************************************
 *
 *  Keyboard matrix scanner A
 *
 ***************************************************************************/
#if !defined(__RK_AS_MATRIX_SCANNER_A__)
#define __RK_AS_MATRIX_SCANNER_A__

#include <stdint.h>
#include "apps/scan/scanner.h"

/**
 * @brief   The working area size for a scanner A thread.
 */
#define rkASMatrixScannerAWASize 128

/***************************************************************************/
// Prototypes:

void rkASMatrixScannerAF( void * );
void scanner_a( RkASMatrixScanner *, RkASMatrix * );

#endif
/* vi: set et sts=2 sw=2 ts=2: */
