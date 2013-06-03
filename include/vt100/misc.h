#ifndef _VT100_MISC_H_
#define _VT100_MISC_H_

#include <common.h>

/* Keypad Application Mode */
#define VT100_SETTING_DECKPAM BIT0

/* Cursor Keys Mode */
#define VT100_SETTING_DECCKM BIT1

/* unsolicited allowed are allowed by computer */
#define VT100_SETTING_UNSOLIC_ALLOW BIT2

/* cursor current state */
#define VT100_SETTING_CURSOR_STATE BIT3

/* Attributes */
#define VT100_SETTING_ATTR_BOLD BIT4
#define VT100_SETTING_ATTR_INVERSE BIT5
#define VT100_SETTING_ATTR_UNDERLINE BIT6
#define VT100_SETTING_ATTR_BLINK BIT7

extern uint8_t vt100_setting;

void vt100_DECKPAM();
void vt100_DECKPNM();
void vt100_RIS();
void vt100_init();

bool_t __is_vt100_malfunctioning();

void vt100_DECTST();

#endif
