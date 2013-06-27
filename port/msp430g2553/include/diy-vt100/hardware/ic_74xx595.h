#ifndef HW_IC_74XX595_H
#define HW_IC_74XX595_H

#include <diy-vt100/common.h>

typedef struct
{
	uint8_t buzzer:1;
	uint8_t led_online:1;
	uint8_t led_offline:1;
	uint8_t led_kbdlock:1;
	uint8_t led_prog1:1;
	uint8_t led_prog2:1;
	uint8_t led_prog3:1;
	uint8_t led_prog4:1;
}__attribute((packed)) ic_74xx595_t;

extern ic_74xx595_t ic_74xx595;

void ic_74xx595_refresh(void);

#endif
