#ifndef _VT100_LED_H_
#define _VT100_LED_H_

#include <common.h>

#define VT100_LED_PDIR P1DIR
#define VT100_LED_POUT P1OUT

#define VT100_LED1 BIT0
#define VT100_LED2 BIT1
#define VT100_LED3 BIT2
#define VT100_LED4 BIT3
#define VT100_LED5 BIT4
#define VT100_LED6 BIT5
#define VT100_LED7 BIT6

#define VT100_LED_ONLINE 	VT100_LED1
#define VT100_LED_LOCAL 	VT100_LED2
#define VT100_LED_KBDLOCK 	VT100_LED3
#define VT100_LED_L1 		VT100_LED4
#define VT100_LED_L2 		VT100_LED5
#define VT100_LED_L3 		VT100_LED6
#define VT100_LED_L4 		VT100_LED7

void vt100_led_init();
void vt100_led_load();

#endif
