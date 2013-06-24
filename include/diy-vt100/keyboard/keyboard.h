#ifndef KBD_H
#define KBD_H

#include <diy-vt100/common.h>
#include <diy-vt100/cqueue.h>

typedef struct
{
	int8_t index;
	uint8_t data;

	struct
	{
		uint8_t _break:1;
		uint8_t caps:1;
		uint8_t ctrl:1;
		uint8_t num:1;
		uint8_t modifier:1;
		uint8_t shift:1;
		uint8_t parity:1;
	} __attribute((packed)) latch;

	uint8_t param;
	cqueue_t queue;
} __attribute((packed)) kbd_t;

extern kbd_t kbd;




#define kbd_latch_high(bit) __high(kbd.latch, bit)
#define kbd_latch_low(bit) __low(kbd.latch, bit)
#define kbd_latch_flip(bit) __flip(kbd.latch, bit)

#define kbd_latch_read(bit) __read(kbd.latch, bit)
#define kbd_latch_ishigh(bit) __ishigh(kbd.latch, bit)
#define kbd_latch_islow(bit) __islow(kbd.latch, bit)

void kbd_ctrl();
void kbd_shift();
void kbd_caps();
void kbd_f5();
void kbd_f4();
void kbd_f3();
void kbd_f2();
void kbd_f1();
void kbd_enter();

void kbd_keypad_0();
void kbd_keypad_1();
void kbd_keypad_2();
void kbd_keypad_3();
void kbd_keypad_4();
void kbd_keypad_5();
void kbd_keypad_6();
void kbd_keypad_7();
void kbd_keypad_8();
void kbd_keypad_9();
void kbd_keypad_dot();
void kbd_keypad_dash();

void kbd_decode();

#endif
