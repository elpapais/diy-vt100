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

void vt100_CUP(void);
void vt100_CUD(void);
void vt100_CUU(void);
void vt100_CUF(void);
void vt100_CUB(void);
void vt100_DECRC(void);
void vt100_DECSC(void);

void vt100_RI(void);
void vt100_IND(void);

#endif
