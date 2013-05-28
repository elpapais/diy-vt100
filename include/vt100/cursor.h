#ifndef _VT100_CURSOR_H_
#define _VT100_CURSOR_H_

#include <common.h>
#include <vt100/param.h>

/* cursor position */
struct __vt100_cursor
{
	row_t row;
	col_t col;
};

#include <vt100/buffer.h>

extern struct __vt100_cursor vt100_cursor;

void vt100_cursor_position();
void vt100_cursor_down();
void vt100_cursor_up();
void vt100_cursor_forward();
void vt100_cursor_backward();
void vt100_cursor_restore();
void vt100_cursor_save();

void vt100_cursor_up_with_scrolldown();
void vt100_cursor_down_with_scrollup();

#endif
