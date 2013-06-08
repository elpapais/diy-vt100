#ifndef _VT100_LED_H_
#define _VT100_LED_H_

#include <common.h>
#include <hardware/led.h>

#define vt100_led_init() led_on(LED_ONLINE)

void vt100_DECLL();

#endif
