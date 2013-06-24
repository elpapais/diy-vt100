#ifndef LED_H
#define LED_H

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

void led_off_allprog();

#endif
