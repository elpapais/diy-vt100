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

typedef enum
{
	PF1, PF2, PF3, PF4
}
kbdpfn_t;

void keyboard_pfn(const kbdpfn_t);

typedef enum
{
	UP,	LEFT, RIGHT, DOWN
}
kbdarrow_t;

void keyboard_arrow(const kbdarrow_t);

inline void keyboard_keyclick_sound(void);

inline void keyboard_keyclick_sound(void)
{
	if(parm_setting.bits.KEYCLICK)
	{
		bell_short();
	}
}

#endif
