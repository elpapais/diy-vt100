#include <vt100/cursor.h>
#include <param.h>
#include <vt100/buffer.h>

struct __vt100_cursor
vt100_cursor,
vt100_cursor_bkp;

/* cursor backward */
void
vt100_CUB()
{
	/* TODO: margin are not supported */
	vt100_buffer[vt100_cursor.row][0].prop |= ROW_TOUCH;
	vt100_cursor.col = constaint(vt100_cursor.col - param.data[0], 0, VT100_WIDTH - 1);
}

/* cursor forward */
void
vt100_CUF()
{
	/* TODO: margin are not supported */
	vt100_buffer[vt100_cursor.row][0].prop |= ROW_TOUCH;
	
	vt100_cursor.col = constaint(vt100_cursor.col + param.data[0], 0, VT100_WIDTH - 1);
}

/* cursor up */
void
vt100_CUU()
{
	/* TODO: margin are not supported | scroll up are not supported */	
	vt100_buffer[vt100_cursor.row][0].prop |= ROW_TOUCH;
	
	vt100_cursor.row = constaint(vt100_cursor.row - param.data[0], 0, VT100_HEIGHT - 1);
}

/* cursor down */
void
vt100_CUD()
{
	/* TODO: margin are not supported | scroll down are not supported */
	vt100_buffer[vt100_cursor.row][0].prop |= ROW_TOUCH;
	
	vt100_cursor.row = constaint(vt100_cursor.row + param.data[0], 0, VT100_HEIGHT - 1);
}

/* cursor position */
void
vt100_CUP()
{
	vt100_buffer[vt100_cursor.row][0].prop |= ROW_TOUCH;
	
	vt100_cursor.row = constaint(param.data[0], 0, VT100_WIDTH - 1);
	vt100_cursor.col = constaint(param.data[1], 0, VT100_WIDTH - 1);
}

/* cursor restore */
void 
vt100_DECRC()
{
	/* TODO: save all settings */
	vt100_cursor = vt100_cursor_bkp;
}

/* cursor save */
void 
vt100_DECSC()
{
	vt100_cursor_bkp = vt100_cursor;
}

/* move down by one line
 * and if at the bottom, scroll up */
void
vt100_IND()
{
	if(!(++vt100_cursor.row < VT100_WIDTH))
	{
		vt100_cursor.row = VT100_WIDTH - 1;
		vt100_buffer_shiftup();
	}
}

/* move up by one line
 * and if at the top, scroll down */
void
vt100_RI()
{
	if(vt100_cursor.row == 0)
	{
		vt100_buffer_shiftdown();
	}
}
