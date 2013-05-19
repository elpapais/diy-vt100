#ifndef _HARDWARE_PORT2_H_
#define _HARDWARE_PORT2_H_

#include <common.h>
#include <cqueue.h>
#include <keyboard/ps2.h>

void port2_init();
void port2_interrupt()__attribute__((interrupt(PORT2_VECTOR)));

#endif
