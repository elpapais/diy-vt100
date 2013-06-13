#ifndef _HW_LED_H_
#define _HW_LED_H_

#include <hardware/ic_74xx595.h>

#define LED_ONLINE 	IC_74xx595_PIN1
#define LED_LOCAL 	IC_74xx595_PIN2
#define LED_KBDLOCK IC_74xx595_PIN3
#define LED_L1 		IC_74xx595_PIN4
#define LED_L2 		IC_74xx595_PIN5
#define LED_L3 		IC_74xx595_PIN6
#define LED_L4 		IC_74xx595_PIN7

#define led_refresh() ic_74xx595_refresh()
#define led_on(led_bit) ic_74xx595_high(led_bit)
#define led_off(led_bit) ic_74xx595_low(led_bit)

#endif
