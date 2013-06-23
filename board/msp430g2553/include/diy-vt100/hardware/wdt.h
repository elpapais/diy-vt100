#ifndef HW_WDT_H
#define HW_WDT_H

#include <diy-vt100/common.h>

void wdt_init();
void wdt_interrupt (void) __attribute__((interrupt(WDT_VECTOR)));

#endif
