#ifndef _HARDWARE_TIMERA_H_
#define _HARDWARE_TIMERA_H_

#include <common.h> 

void timerA_init();
void timerA0_interrupt (void) __attribute__((interrupt(TIMER0_A0_VECTOR)));

#endif
