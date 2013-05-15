#ifndef _VT100_H_
#define _VT100_H_

#include <vt100/bell.h>
#include <vt100/buffer.h>
#include <vt100/cursor.h>
#include <vt100/param.h>
#include <vt100/pin.h>
#include <vt100/setting.h>
#include <vt100/type.h>
#include <vt100/screen.h>
#include <vt100/led.h>
#include <vt100/tab.h>
#include <nokia1100.h>
#include <common.h>
#include <uart.h>

void vt100_init();
bool_t __is_vt100_malfunctioning();

void vt100_invoke_confidence_test();
void vt100_set_topbottom_margin();
void vt100_to_reset_state();
void vt100_set_horizontal_tabulation();
void vt100_keypad_appmode();
void vt100_keypad_nummode();

#endif
