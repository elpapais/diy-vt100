#ifndef _VT100_TYPE_H_
#define _VT100_TYPE_H_

#include <vt100/screen.h>
#include <vt100/param.h>
#include <common.h>

struct __mode
{
	/* Application  Mode :1 , Keypad Mode:0 */
	uint8_t keypad:1;
	
	/* unsolicited allowed are allowed by computer */
	uint8_t unsolicited_allowed:1;
	
	/* cursor current state */
	uint8_t current_state:1;
	
	uint8_t attr_bold:1;
	
	uint8_t attr_inverse:1;
	
	uint8_t attr_blink:1;
	
	uint8_t attr_underline:1;
};

struct __char
{
	/* actual data to print */
	uint8_t data;
	
	/* DATA attributes */
	uint8_t bold:1;
	uint8_t underline:1;
	uint8_t blink:1;
	uint8_t inverse:1;
	
	/* Below: these are only used for coloumn 1 (TO SAVE RAM) */
	
	/* is row touched */
	uint8_t touched:1;
	
	/* is it the double height top part */
	uint8_t double_height_top:1;
	
	/* is it the double height bottom part */
	uint8_t double_height_bottom:1;
	
	/* is this a double width line */
	uint8_t double_width:1;
};

/* cursor position */
struct __cursor
{
	row_t row;
	col_t col;
};

/* terminal object */
struct __vt100
{
	/* cursor position */
	struct __cursor cursor;
	struct __char screen[VT100_HEIGHT][VT100_WIDTH];
	
	uint8_t param[VT100_PARAM_QUEUE_SIZE];
	
	uint8_t data;
	
	/* setting for vt100 */
	struct __mode mode;
};
#endif
