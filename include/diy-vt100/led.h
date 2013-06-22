#ifndef _LED_H_
#define _LED_H_

typedef enum
{
	ONLINE,
	LOCAL,
	KBDLOCK,
	PROG1,
	PROG2,
	PROG3,
	PROG4
} led_t;

void led_on(led_t);
void led_off(led_t);

#endif
