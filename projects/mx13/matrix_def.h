/****************************************************************************
 *
 *  Keyboard matrix definition
 *
 ***************************************************************************/
#if !defined(__RK_MX13_MATRIX_DEF__)
#define __RK_MX13_MATRIX_DEF__


#include "apps/scan/matrix.h"

#define KBD_MATRIX_NUM_ROWS    5
#define KBD_MATRIX_NUM_COLS    19

#define ROW_0 { .portid = IOPORT1, .mask = 0b00000001, .offset = 0 }
#define ROW_1 { .portid = IOPORT1, .mask = 0b00000010, .offset = 1 }
#define ROW_2 { .portid = IOPORT1, .mask = 0b00000100, .offset = 2 }
#define ROW_3 { .portid = IOPORT1, .mask = 0b00001000, .offset = 3 }
#define ROW_4 { .portid = IOPORT1, .mask = 0b00010000, .offset = 4 }

#define COL_00 { .portid = IOPORT3, .mask = 0b00001000, .offset = 3 }
#define COL_01 { .portid = IOPORT3, .mask = 0b00000100, .offset = 2 }
#define COL_02 { .portid = IOPORT3, .mask = 0b00000010, .offset = 1 }
#define COL_03 { .portid = IOPORT3, .mask = 0b00000001, .offset = 0 }
#define COL_04 { .portid = IOPORT6, .mask = 0b01000000, .offset = 6 }
#define COL_05 { .portid = IOPORT6, .mask = 0b00100000, .offset = 5 }
#define COL_06 { .portid = IOPORT6, .mask = 0b00010000, .offset = 4 }
#define COL_07 { .portid = IOPORT6, .mask = 0b00001000, .offset = 3 }
#define COL_08 { .portid = IOPORT6, .mask = 0b00000100, .offset = 2 }
#define COL_09 { .portid = IOPORT6, .mask = 0b00000010, .offset = 1 }
#define COL_10 { .portid = IOPORT5, .mask = 0b00000010, .offset = 1 }
#define COL_11 { .portid = IOPORT5, .mask = 0b00000001, .offset = 0 }
#define COL_12 { .portid = IOPORT4, .mask = 0b10000000, .offset = 7 }
#define COL_13 { .portid = IOPORT5, .mask = 0b10000000, .offset = 7 }
#define COL_14 { .portid = IOPORT6, .mask = 0b00000001, .offset = 0 }
#define COL_15 { .portid = IOPORT1, .mask = 0b00100000, .offset = 5 }
#define COL_16 { .portid = IOPORT4, .mask = 0b00010000, .offset = 4 }
#define COL_17 { .portid = IOPORT4, .mask = 0b00001000, .offset = 3 }
#define COL_18 { .portid = IOPORT5, .mask = 0b01000000, .offset = 6 }

#define ROW_DEFS \
  ROW_0, ROW_1, ROW_2, ROW_3, ROW_4

#define COL_DEFS \
  COL_00, COL_01, COL_02, COL_03, COL_04, \
  COL_05, COL_06, COL_07, COL_08, COL_09, \
  COL_10, COL_11, COL_12, COL_13, COL_14, \
  COL_15, COL_16, COL_17, COL_18

extern const RkASMatrixLayout matrix_layout;
extern const RkASMatrixLayout matrix_layout_P;


/***************************************************************************/

#endif

/* vi: set et sts=2 sw=2 ts=2: */
