#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include <msp430.h>

#define hardware_init() msp430_init()
void msp430_init();

#define __refresh_finished() _BIS_SR(LPM1_bits + GIE)

#define hardware_reset() (WDTCTL = 0)

#endif
