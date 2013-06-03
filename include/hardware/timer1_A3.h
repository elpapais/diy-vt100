#ifndef _HARDWARE_TIMER1_A3_H_
#define _HARDWARE_TIMER1_A3_H_

#include <common.h> 

#define TIMER1_A3_TACTL TA1CTL
#define TIMER1_A3_TACCR0 TA1CCR0
#define TIMER1_A3_TACCR1 TA1CCR1
#define TIMER1_A3_TACCTL0 TA1CTL

#define TIMER1_A3_PWM_INIT 150

#define TIMER1_A3_PWM_MAX 255
#define TIMER1_A3_PWM_MIN 0

void timer1_A3_pwm(uint8_t value);

void timer1_A3_init();

#endif
