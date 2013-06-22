#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include <msp430.h>

void hardware_init();

#define __refresh_finished() _BIS_SR(LPM1_bits + GIE)

void hardware_reset();

#endif
