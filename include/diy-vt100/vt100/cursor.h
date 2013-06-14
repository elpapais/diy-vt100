#ifndef _VT100_CURSOR_H_
#define _VT100_CURSOR_H_

#include <diy-vt100/common.h>

/* cursor position */
struct __vt100_cursor
{
	row_t row;
	col_t col;
};

extern struct __vt100_cursor vt100_cursor;
extern struct __vt100_cursor vt100_cursor_bkp;

void vt100_CUP();
void vt100_CUD();
void vt100_CUU();
void vt100_CUF();
void vt100_CUB();
void vt100_DECRC();
void vt100_DECSC();

void vt100_RI();
void vt100_IND();

#endif
