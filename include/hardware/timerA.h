#ifndef _HARDWARE_TIMERA_H_
#define _HARDWARE_TIMERA_H_

#include <common.h>
#include <msp430.h>
#include <vt100/vt100.h>
#include <control.h>
#include <uart.h>
#include <keyboard/ps2.h>

void timerA_init();
void timerA0_interrupt (void) __attribute__((interrupt(TIMER0_A0_VECTOR)));

#endif
