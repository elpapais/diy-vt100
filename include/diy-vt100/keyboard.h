#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <diy-vt100/common.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/bell.h>

/* A-Z , a-z, 0-9 special-symbols */
void keyboard_other(const uint8_t ascii);

void keyboard_escape(void);
void keyboard_tab(void);
void keyboard_linefeed(void);
void keyboard_return(void);
void keyboard_delete(void);
void keyboard_break(void);
void keyboard_setup(void);
void keyboard_noscroll(void);
void keyboard_backspace(void);

void keyboard_keypad_comma(void);
void keyboard_keypad_plus(void);
void keyboard_keypad_enter(void);
void keyboard_keypad_num(const uint8_t num);
void keyboard_keypad_dot(void);
void keyboard_keypad_dash(void);

#define PF1 'P'
#define PF2 'Q'
#define PF3 'R'
#define PF4 'S'

void keyboard_pfn(const uint8_t);

#define UP 		'A'
#define DOWN 	'B'
#define RIGHT 	'C'
#define LEFT 	'D'

void keyboard_arrow(const uint8_t);

inline void keyboard_keyclick_sound(void);

inline void keyboard_keyclick_sound(void)
{
	if(parm_setting.bits.KEYCLICK)
	{
		bell_short();
	}
}

#endif
