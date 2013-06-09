#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <hardware/timer0_A3.h>

#define buzzer_long() timer0_A3_start(0xFFFF) 
#define buzzer_short() timer0_A3_start(0x4000)

#endif
