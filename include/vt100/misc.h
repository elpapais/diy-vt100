#ifndef _VT100_MISC_H_
#define _VT100_MISC_H_

#include <common.h>
#include <vt100/cursor.h>

/* Application  Mode :1 , Keypad Mode:0 */
#define VT100_SETTING_MODE_KEYPAD BIT0
/* unsolicited allowed are allowed by computer */
#define VT100_SETTING_MODE_UNSOLIC_ALLOW BIT1
/* cursor current state */
#define VT100_SETTING_MODE_CURSOR_STATE BIT2

/* Attributes */
#define VT100_SETTING_MODE_ATTR_BOLD BIT3
#define VT100_SETTING_MODE_ATTR_INVERSE BIT4
#define VT100_SETTING_MODE_ATTR_UNDERLINE BIT5
#define VT100_SETTING_MODE_ATTR_BLINK BIT6

/* compaitble mode(0:vt52, 1:ansi) */
#define VT100_SETTING_MODE_COMPATIBLE BIT7

/* cursor key mode(0:reset, 1:set) */
#define VT100_SETTING_MODE_CURSOR_KEY BIT8

struct __vt100_setting
{
	uint16_t mode;
	struct __vt100_cursor cursor_bkp;
};

extern struct __vt100_setting vt100_setting;

void vt100_setting_save(void *src, uint8_t size);
void vt100_setting_load(void *dest, uint8_t size);

void vt100_keypad_appmode();
void vt100_keypad_nummode();
void vt100_to_reset_state();
void vt100_init();

bool_t __is_vt100_malfunctioning();

void vt100_invoke_confidence_test();

#endif
