#ifndef _VT100_MISC_H_
#define _VT100_MISC_H_

#include <common.h>

/* Application  Mode :1 , Keypad Mode:0 */
#define VT100_SETTING_KEYPAD BIT0
/* unsolicited allowed are allowed by computer */
#define VT100_SETTING_UNSOLIC_ALLOW BIT1
/* cursor current state */
#define VT100_SETTING_CURSOR_STATE BIT2

/* Attributes */
#define VT100_SETTING_ATTR_BOLD BIT3
#define VT100_SETTING_ATTR_INVERSE BIT4
#define VT100_SETTING_ATTR_UNDERLINE BIT5
#define VT100_SETTING_ATTR_BLINK BIT6

extern uint8_t vt100_setting;

void vt100_DECKPAM();
void vt100_DECKPNM();
void vt100_RIS();
void vt100_init();

bool_t __is_vt100_malfunctioning();

void vt100_DECTST();

#endif
