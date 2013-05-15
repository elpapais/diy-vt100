#ifndef _VT100_CURSOR_H_
#define _VT100_CURSOR_H_

#include <common.h>
#include <vt100/extern.h>
#include <nokia1100.h>

#define vt100_cursor_gotocol(c) (vt100.cursor.col = c)
#define vt100_cursor_gotorow(r) (vt100.cursor.row = r)
#define vt100_cursor_goto(r,c) vt100_cursor_gotorow(r);vt100_cursor_gotocol(c)
void vt100_cursor();

void timer0_interrupt (void) __attribute__((interrupt(TIMER0_A0_VECTOR)));

void vt100_cursor_position();
void vt100_cursor_down();
void vt100_cursor_up();
void vt100_cursor_forward();
void vt100_cursor_backward();
void vt100_restore_cursor();
void vt100_save_cursor();

#endif
