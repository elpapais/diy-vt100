#ifndef _HW_TIMER0_A3_H_
#define _HW_TIMER0_A3_H_

#include <diy-vt100/common.h> 

#define TIMER0_A3_TACTL TA0CTL
#define TIMER0_A3_TACCR0 TA0CCR0
#define TIMER0_A3_TACCR1 TA0CCR1
#define TIMER0_A3_TACCTL0 TA0CCTL0

#define BUZZER 	IC_74xx595_PIN0

void timer0_A3_start(const uint16_t delay);
void timer0_A0_interrupt (void) __attribute__((interrupt(TIMER0_A0_VECTOR)));

#endif
