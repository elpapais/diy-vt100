#ifndef _INTERRUPT_PORT2_H_
#define _INTERRUPT_PORT2_H_

#include <common.h>
#include <cqueue.h>
#include <keyboard/ps2.h>

#define port2_init() keyboard_ps2_init()
void port2_interrupt()__attribute__((interrupt(PORT2_VECTOR)));

#endif
