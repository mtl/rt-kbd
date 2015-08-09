/****************************************************************************
 *
 *  Main
 *
 ***************************************************************************/

/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


//---------------------------------------------------------------------------

#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include "hal.h"
#include "nil.h"
#include "apps/scan/scanner.h"
#include "apps/scan/scanner_a.h"
#include "matrix_def.h"


//---------------------------------------------------------------------------

/*
 * Thread 1.
 */
THD_WORKING_AREA(waThread1, 128);
THD_FUNCTION(Thread1, arg) {

  (void)arg;

  while (true) {
    palTogglePad(IOPORT2, PORTD_LED1);
    chThdSleepMilliseconds(500);
  }

}

/*
 * Thread 2.
 */
THD_WORKING_AREA(waThread2, 128);
THD_FUNCTION(Thread2, arg) {

  (void)arg;

  /*
   * Activates the serial driver 1 using the driver default configuration.
   * PA9 and PA10 are routed to USART1.
   */
  sdStart(&SD2, NULL);

  while (true) {
    chnWrite(&SD2, (const uint8_t *)"Hello World!\r\n", 14);
    chThdSleepMilliseconds(2000);
  }
}

/*
 * Threads static table, one entry per thread. The number of entries must
 * match NIL_CFG_NUM_THREADS.
 */
THD_TABLE_BEGIN
  THD_TABLE_ENTRY(waThread1, "blinker", Thread1, NULL)
  THD_TABLE_ENTRY(waThread2, "hello", Thread2, NULL)
THD_TABLE_END

#define RK_AS_MATRIX_SCANNER_THD( scanner, id, name, config ) \
  THD_TABLE_ENTRY( id ## WA, name, scanner ## F, config )



/*
 * Application entry point.
 */
int main(void) {

  /* Disable watchdog if enabled by bootloader/fuses */
  MCUSR &= ~(1 << WDRF);
  wdt_disable();

  /* Disable clock division */
  clock_prescale_set(clock_div_1);

  /* Global interrupt enable: */
  sei();


  // Matrix with layout from RAM:
  DEFINE_SCANNER( scanner, matrix, false );
//  rkas_init( &scanner );

  // Matrix with layout from progmem:
  DEFINE_SCANNER( scanner_P, matrix_P, true );
//  rkas_init( &scanner_P );

  // Matrix with layout from RAM, but loaded from EEPROM:
  RkASMatrix matrix_E;
  rkas_load_from_eeprom( &matrix_E, NULL );
  DEFINE_SCANNER( scanner_E, matrix_E, false );
//  rkas_init( &scanner_E );

//  KBDMatrixScanner scanner;
//  scanner_a( &scanner, matrix );
//  scanner_a( &scanner, matrix_P );



  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /* This is now the idle thread loop, you may perform here a low priority
     task but you must never try to sleep or wait in this loop. Note that
     this tasks runs at the lowest priority level so any instruction added
     here will be executed after all other tasks have been started.*/
  while (true) {
  }
}


//===========================================================================


/* vi: set et sts=2 sw=2 ts=2: */
