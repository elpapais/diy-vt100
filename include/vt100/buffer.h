#ifndef _VT100_CHAR_H_
#define _VT100_CHAR_H_

#include <common.h>
#include <nokia1100.h>

#define VT100_WIDTH NOKIA1100_COLOUMN
#define VT100_HEIGHT NOKIA1100_ROW

#define VT100_CHAR_PROP_BOLD BIT0
#define VT100_CHAR_PROP_UNDERLINE BIT1
#define VT100_CHAR_PROP_INVERSE BIT2

/* row use only */
#define VT100_CHAR_PROP_TOUCH BIT3
#define VT100_CHAR_PROP_DOUBLE_HEIGHT_BOTTOM BIT4
#define VT100_CHAR_PROP_DOUBLE_HEIGHT_TOP BIT5
#define VT100_CHAR_PROP_DOUBLE_WIDTH BIT6

/* coloumn use only */
#define VT100_CHAR_PROP_TAB BIT7

struct __vt100_char
{
	/* actual data to print */
	uint8_t data;
	uint8_t prop;
};

extern struct __vt100_char vt100_buffer[VT100_HEIGHT][VT100_WIDTH];

void vt100_buffer_putchar();
void vt100_buffer_shiftup();
void vt100_buffer_shiftdown();

void vt100_DECALN();

void vt100_LF();
void vt100_NEL();
void vt100_CR();

void vt100_ED();
void vt100_EL();

void vt100_buffer_copy(const struct __vt100_char buffer[VT100_HEIGHT][VT100_WIDTH]);

#endif
