#ifndef _VT100_CHAR_H_
#define _VT100_CHAR_H_

#include <diy-vt100/common.h>
#include <diy-vt100/screen.h>

#define VT100_WIDTH SCREEN_WIDTH
#define VT100_HEIGHT SCREEN_HEIGHT

#define DATA_BOLD BIT0
#define DATA_UNDERLINE BIT1
#define DATA_INVERSE BIT2
#define DATA_BLINK BIT3

/* row use only */
#define ROW_TOUCH BIT4
#define ROW_DOUBLE_HEIGHT_BOT BIT5
#define ROW_DOUBLE_HEIGHT_TOP BIT6
#define ROW_DOUBLE_WIDTH BIT7

struct __vt100_char
{
	/* actual data to print */
	uint8_t data;
	uint8_t prop;
};

extern struct __vt100_char vt100_buffer[VT100_HEIGHT][VT100_WIDTH];

#define vt100_buffer_prop_read(i, j, props) __read(vt100_buffer[i][j].prop, props)
#define vt100_buffer_prop_high(i, j, props) __high(vt100_buffer[i][j].prop, props)
#define vt100_buffer_prop_low(i, j, props) __low(vt100_buffer[i][j].prop, props)
#define vt100_buffer_prop_clear(i, j) (vt100_buffer[i][j].prop = 0)

#define vt100_buffer_row_read(i, props) vt100_buffer_prop_read(i, 0, props)
#define vt100_buffer_row_high(i, props) vt100_buffer_prop_high(i, 0, props)
#define vt100_buffer_row_low(i, props) vt100_buffer_prop_low(i, 0, props)

#define vt100_buffer_row_touched(i) vt100_buffer_row_read(i, ROW_TOUCH)
#define vt100_buffer_row_touch(i) vt100_buffer_row_high(i, ROW_TOUCH)

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
