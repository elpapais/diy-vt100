#ifndef _HW_BELL_H_
#define _HW_BELL_H_

#include <diy-vt100/hardware/timer0_A3.h>

#define bell_long() timer0_A3_start(0xFFFF) 
#define bell_short() timer0_A3_start(0x4000)

#endif
