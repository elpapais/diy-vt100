#ifndef _VT100_BUFFER_H_
#define _VT100_BUFFER_H_

#include <common.h>
#include <nokia1100.h>
#include <vt100/param.h>
#include <vt100/misc.h>
#include <vt100/cursor.h>

#define VT100_WIDTH NOKIA1100_COLOUMN
#define VT100_HEIGHT NOKIA1100_ROW

#define VT100_BUFFER_PROP_BOLD BIT0
#define VT100_BUFFER_PROP_UNDERLINE BIT1
#define VT100_BUFFER_PROP_INVERSE BIT2

/* row use only */
#define VT100_BUFFER_PROP_TOUCH BIT3
#define VT100_BUFFER_PROP_DOUBLE_HEIGHT_BOTTOM BIT4
#define VT100_BUFFER_PROP_DOUBLE_HEIGHT_TOP BIT5
#define VT100_BUFFER_PROP_DOUBLE_WIDTH BIT6

/* coloumn use only */
#define VT100_BUFFER_PROP_TAB BIT7

struct __vt100_char
{
	/* actual data to print */
	uint8_t data;
	uint8_t prop;
};

extern struct __vt100_char vt100_buffer[VT100_HEIGHT][VT100_WIDTH];

void vt100_buffer_putchar();
void vt100_buffer_newrow();
void vt100_buffer_shiftup();
void vt100_buffer_shiftdown();
void vt100_buffer_clear_char(const row_t i, const col_t j);
void vt100_buffer_fill_E();
void vt100_buffer_erase();

#endif
