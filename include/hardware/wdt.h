#ifndef _WDT_H_
#define _WDT_H_

#include <common.h>

#define WDT_CYCLES_MAX 64

void wdt_init();
void wdt_interrupt (void) __attribute__((interrupt(WDT_VECTOR)));

#endif
