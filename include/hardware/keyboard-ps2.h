#ifndef _KEYBOARD_PS2_H_
#define _KEYBOARD_PS2_H_

#include <common.h>
#include <cqueue.h>

#define KEYBOARD_PS2_MODE_LATCH_CTRL BIT0
#define KEYBOARD_PS2_MODE_LATCH_NUM BIT1
#define KEYBOARD_PS2_MODE_LATCH_CAPS BIT2
#define KEYBOARD_PS2_MODE_LATCH_SHIFT BIT3
#define KEYBOARD_PS2_MODE_PARITY BIT4
#define KEYBOARD_PS2_MODE_MODIFIER BIT5
#define KEYBOARD_PS2_MODE_BREAK BIT6
//#define KEYBOARD_PS2_MODE_LATCH_GUI
//#define KEYBOARD_PS2_MODE_LATCH_ALT

#define KEYBOARD_PS2_ENTER ASCII_LF

struct __keyboard_ps2
{
	int8_t index;
	uint8_t mode;
	uint8_t data;
	
	uint8_t param;
	struct __cqueue data_queue;
};

#define KEYBOARD_PS2_KEYMAP_SIZE 130

#define keyboard_ps2_scancode_num(ch, chalt) {0, {ch, chalt}}
#define keyboard_ps2_scancode_special(ch, chalt) {0, {ch, chalt}}
#define keyboard_ps2_scancode_alpha(ch, chalt) {(callback_t)1, {ch, chalt}}
#define keyboard_ps2_scancode_callback(cb) {cb, {0, 0}}
#define keyboard_ps2_scancode_ignore() {0, {0, 0}}

struct __keyboard_ps2_scancode
{
	/*
	 * 0 = do not exists
	 * 1 = character is affected by caps status
	 * other = call
	 */
	callback_t callback;
	
	/* 0:main, 1:replacement */
	uint8_t ch[2];
};

#define KEYBOARD_PS2_SCANCODE_SIZE 126

extern struct __keyboard_ps2 keyboard_ps2;
extern const struct __keyboard_ps2_scancode keyboard_ps2_scancode_en[KEYBOARD_PS2_SCANCODE_SIZE];

void keyboard_ps2_data_decode();

void keyboard_ps2_scancode_callback_ctrl();
void keyboard_ps2_scancode_callback_shift();
void keyboard_ps2_scancode_callback_caps();
void keyboard_ps2_scancode_callback_f5();
void keyboard_ps2_scancode_callback_f4();
void keyboard_ps2_scancode_callback_f3();
void keyboard_ps2_scancode_callback_f2();
void keyboard_ps2_scancode_callback_f1();
void keyboard_ps2_scancode_callback_enter();

void keyboard_ps2_scancode_callback_keypad_0();
void keyboard_ps2_scancode_callback_keypad_1();
void keyboard_ps2_scancode_callback_keypad_2();
void keyboard_ps2_scancode_callback_keypad_3();
void keyboard_ps2_scancode_callback_keypad_4();
void keyboard_ps2_scancode_callback_keypad_5();
void keyboard_ps2_scancode_callback_keypad_6();
void keyboard_ps2_scancode_callback_keypad_7();
void keyboard_ps2_scancode_callback_keypad_8();
void keyboard_ps2_scancode_callback_keypad_9();
void keyboard_ps2_scancode_callback_keypad_dot();
void keyboard_ps2_scancode_callback_keypad_dash();

#endif
