#ifndef _VT100_LED_H_
#define _VT100_LED_H_

#include <common.h>
#include <hardware/ic_74xx595.h>

#define vt100_led_init() ic_74xx595_high(VT100_LED_ONLINE)

void vt100_DECLL();

#endif
