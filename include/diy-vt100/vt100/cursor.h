#ifndef VT100_CURSOR_H
#define VT100_CURSOR_H

#include <diy-vt100/common.h>
#include <diy-vt100/screen.h>

/* cursor position */
struct __cursor
{
	row_t row;
	col_t col;
};

extern struct __cursor vt100_cursor;
extern struct __cursor vt100_cursor_bkp;

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
