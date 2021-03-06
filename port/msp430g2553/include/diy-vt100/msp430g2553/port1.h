#ifndef HW_PORT1_H
#define HW_PORT1_H

#include <diy-vt100/common.h>

#define SETUP_BUTTON BIT3

#define IC_74XX595_DATA BIT0
#define IC_74XX595_STCP BIT4
#define IC_74XX595_SHCP BIT5

#define port1_low(bits) 	__low(P1OUT, bits)
#define port1_high(bits)	__high(P1OUT, bits)
#define port1_flip(bits)	__flip(P1OUT, bits)

#endif
