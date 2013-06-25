#ifndef KBD_H
#define KBD_H

#include <diy-vt100/common.h>
#include <diy-vt100/hardware/cqueue.h>

#define HW_KBD_SCANCODE_SIZE 126

typedef struct
{
	/*
	 * 0 = do not exists
	 * 1 = character is affected by caps status
	 * other = call
	 */
	callback_t callback;
	
	/* 0:main, 1:replacement */
	uint8_t ch[2];
}hwkbdscancode_t;

extern const hwkbdscancode_t hw_kbd_scancode[HW_KBD_SCANCODE_SIZE];

typedef struct
{
	int8_t index;
	uint8_t data;
	uint8_t param;
	cqueue_t queue;
} __attribute((packed)) hwkbd_t;

extern hwkbd_t hw_kbd;

void hw_kbd_ctrl(void);
void hw_kbd_shift(void);
void hw_kbd_caps(void);
void hw_kbd_f5(void);
void hw_kbd_f4(void);
void hw_kbd_f3(void);
void hw_kbd_f2(void);
void hw_kbd_f1(void);
void hw_kbd_enter(void);

void hw_kbd_keypad_0(void);
void hw_kbd_keypad_1(void);
void hw_kbd_keypad_2(void);
void hw_kbd_keypad_3(void);
void hw_kbd_keypad_4(void);
void hw_kbd_keypad_5(void);
void hw_kbd_keypad_6(void);
void hw_kbd_keypad_7(void);
void hw_kbd_keypad_8(void);
void hw_kbd_keypad_9(void);
void hw_kbd_keypad_dot(void);
void hw_kbd_keypad_dash(void);

void hw_kbd_decode(void);

#endif
