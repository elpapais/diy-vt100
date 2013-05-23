#ifndef _KEYBOARD_PS2_H_
#define _KEYBOARD_PS2_H_

#include <common.h>
#include <uart.h>

#define KEYBOARD_PS2_PDIR P2DIR
#define KEYBOARD_PS2_PIN  P2IN
#define KEYBOARD_PS2_POUT P2OUT
#define KEYBOARD_PS2_PIFG P2IFG
#define KEYBOARD_PS2_PIES P2IES
#define KEYBOARD_PS2_PIE  P2IE
#define KEYBOARD_PS2_PREN P2REN

#define KEYBOARD_PS2_DATA BIT3
#define KEYBOARD_PS2_CLK BIT4

/* derivative: http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html */

/* scancodes */
#define KEYBOARD_PS2_TAB						ASCII_HT //9
#define KEYBOARD_PS2_ENTER						ASCII_LF //13
#define KEYBOARD_PS2_BACKSPACE					ASCII_BS //08
#define KEYBOARD_PS2_ESCAPE						ASCII_ESCAPE //27
#define KEYBOARD_PS2_INSERT						0
#define KEYBOARD_PS2_DELETE						ASCII_DEL //127
#define KEYBOARD_PS2_HOME						0
#define KEYBOARD_PS2_END						0
#define KEYBOARD_PS2_PAGEUP						25
#define KEYBOARD_PS2_PAGEDOWN					26
#define KEYBOARD_PS2_UPARROW					11
#define KEYBOARD_PS2_LEFTARROW					8
#define KEYBOARD_PS2_DOWNARROW					10
#define KEYBOARD_PS2_RIGHTARROW					21
#define KEYBOARD_PS2_F1							0
#define KEYBOARD_PS2_F2							0
#define KEYBOARD_PS2_F3							0
#define KEYBOARD_PS2_F4							0
#define KEYBOARD_PS2_F5							0
#define KEYBOARD_PS2_F6							0
#define KEYBOARD_PS2_F7							0
#define KEYBOARD_PS2_F8							0
#define KEYBOARD_PS2_F9							0
#define KEYBOARD_PS2_F10						0
#define KEYBOARD_PS2_F11						0
#define KEYBOARD_PS2_F12						0
#define KEYBOARD_PS2_SCROLL						0

#define KEYBOARD_PS2_KEYMAP_SIZE 136

#define keyboard_ps2_scancode_char(ch1, ch2) {ch1, ch2}

#define KEYBOARD_PS2_MODE_LATCH_CTRL BIT0
#define KEYBOARD_PS2_MODE_LATCH_NUM BIT1
#define KEYBOARD_PS2_MODE_LATCH_ALT BIT2
#define KEYBOARD_PS2_MODE_LATCH_CAPS BIT3
#define KEYBOARD_PS2_MODE_LATCH_SHIFT BIT4
#define KEYBOARD_PS2_MODE_PARITY BIT5
#define KEYBOARD_PS2_MODE_MODIFIER BIT6
#define KEYBOARD_PS2_MODE_MAKE BIT7
//#define KEYBOARD_PS2_MODE_LATCH_GUI

struct __keyboard_ps2
{
	int8_t index;
	uint8_t mode;
	uint8_t data;
};

extern struct __keyboard_ps2 keyboard_ps2;
extern const uint8_t keyboard_ps2_scancode_en[KEYBOARD_PS2_KEYMAP_SIZE][2];

void keyboard_ps2_init();
void keyboard_ps2_data_decode();
void keyboard_ps2_resolve_scancode();

#endif
