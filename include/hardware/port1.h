#ifndef _HARDWARE_PORT1_H_
#define _HARDWARE_PORT1_H_

#include <common.h>

#define SETUP_BUTTON BIT3

void port1_init();
void port1_interrupt()__attribute__((interrupt(PORT1_VECTOR)));


#endif
