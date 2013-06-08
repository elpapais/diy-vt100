#ifndef _74XX595_H_
#define _74XX595_H_

#include <common.h>

#define VT100_BELL 			BIT0
#define VT100_LED_ONLINE 	BIT1
#define VT100_LED_LOCAL 	BIT2
#define VT100_LED_KBDLOCK 	BIT3
#define VT100_LED_L1 		BIT4
#define VT100_LED_L2 		BIT5
#define VT100_LED_L3 		BIT6
#define VT100_LED_L4 		BIT7

extern uint8_t ic_74xx595;

#define ic_74xx595_high(bits) 	__high(ic_74xx595, bits)
#define ic_74xx595_low(bits) 	__low(ic_74xx595, bits)
#define ic_74xx595_flip(bits) 	__flip(ic_74xx595, bits)

#define ic_74xx595_init()

void ic_74xx595_refresh();

#endif
