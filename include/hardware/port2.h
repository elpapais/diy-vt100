#ifndef _HARDWARE_PORT2_H_
#define _HARDWARE_PORT2_H_

#include <common.h>

/* === for keyboard === */
#define KEYBOARD_PS2_DATA BIT0
#define KEYBOARD_PS2_CLK BIT1

/* NOTE: using p2.2 for timer1_A3 PWM for LCD */

#define NOKIA1100_SS 	BIT3
#define NOKIA1100_MOSI 	BIT4
#define NOKIA1100_CLK 	BIT5

#define port2_low(bits) 	__low(P2OUT, bits)
#define port2_high(bits)	__high(P2OUT, bits)
#define port2_flip(bits)	__flip(P2OUT, bits)

/* ==== */
void port2_init();
void port2_interrupt()__attribute__((interrupt(PORT2_VECTOR)));

#endif
