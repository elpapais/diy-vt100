#ifndef _HW_IC_74XX595_H_
#define _HW_IC_74XX595_H_

#include <diy-vt100/common.h>

extern uint8_t ic_74xx595;

#define IC_74xx595_PIN0 BIT0
#define IC_74xx595_PIN1 BIT1
#define IC_74xx595_PIN2 BIT2
#define IC_74xx595_PIN3 BIT3
#define IC_74xx595_PIN4 BIT4
#define IC_74xx595_PIN5 BIT5
#define IC_74xx595_PIN6 BIT6
#define IC_74xx595_PIN7 BIT7

#define ic_74xx595_high(bits) 	__high(ic_74xx595, bits)
#define ic_74xx595_low(bits) 	__low(ic_74xx595, bits)
#define ic_74xx595_flip(bits) 	__flip(ic_74xx595, bits)

#define ic_74xx595_init()

void ic_74xx595_refresh();

#endif
