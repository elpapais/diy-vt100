#ifndef _HW_TIMER1_A3_H_
#define _HW_TIMER1_A3_H_

#include <diy-vt100/common.h> 

#define TIMER1_A3_TACTL TA1CTL
#define TIMER1_A3_TACCR0 TA1CCR0
#define TIMER1_A3_TACCR1 TA1CCR1
#define TIMER1_A3_TACCTL0 TA1CTL

#define TIMER1_A3_PWM_INIT 3

#define TIMER1_A3_PWM_MAX 5
#define TIMER1_A3_PWM_MIN 0

void timer1_A3_pwm(uint8_t value);

void timer1_A3_init();

#endif
