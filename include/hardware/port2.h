#ifndef _HARDWARE_PORT2_H_
#define _HARDWARE_PORT2_H_

#include <common.h>

/* === for keyboard === */
#define KEYBOARD_PS2_DATA BIT0
#define KEYBOARD_PS2_CLK BIT1

/* NOTE: using p2.2 for timer1_A3 PWM for LCD */

/* === for nokia ==== */
#define NOKIA1100_SS 	BIT3
#define NOKIA1100_MOSI 	BIT4
#define NOKIA1100_CLK 	BIT5

#define nokia1100_ss_high() (P2OUT |= NOKIA1100_SS)
#define nokia1100_ss_low() (P2OUT &= ~NOKIA1100_SS)

#define nokia1100_mosi_low() (P2OUT &= ~NOKIA1100_MOSI)
#define nokia1100_mosi_high() (P2OUT |= NOKIA1100_MOSI)

#define nokia1100_clk_low() (P2OUT &= ~NOKIA1100_CLK)
#define nokia1100_clk_high() (P2OUT |= NOKIA1100_CLK)

/* ==== */
void port2_init();
void port2_interrupt()__attribute__((interrupt(PORT2_VECTOR)));

#endif
