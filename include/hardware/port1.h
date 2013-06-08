#ifndef _HARDWARE_PORT1_H_
#define _HARDWARE_PORT1_H_

#include <common.h>

#define SETUP_BUTTON BIT3

#define IC_74XX595_DATA BIT0
#define IC_74XX595_STCP BIT4
#define IC_74XX595_SHCP BIT5

#define port1_low(bits) 	__low(P1OUT, bits)
#define port1_high(bits)	__high(P1OUT, bits)
#define port1_flip(bits)	__flip(P1OUT, bits)

void port1_init();
void port1_interrupt()__attribute__((interrupt(PORT1_VECTOR)));


#endif
