#include <vt100/cursor.h>
#include <param.h>
#include <vt100/buffer.h>

struct __vt100_cursor
vt100_cursor,
vt100_cursor_bkp;

void
vt100_cursor_backward()
{
	/* TODO: margin are not supported */
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_CHAR_PROP_TOUCH;
	vt100_cursor.col = constaint(vt100_cursor.col - param.data[0], 0, VT100_WIDTH - 1);
}

void
vt100_cursor_forward()
{
	/* TODO: margin are not supported */
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_CHAR_PROP_TOUCH;
	
	vt100_cursor.col = constaint(vt100_cursor.col + param.data[0], 0, VT100_WIDTH - 1);
}

void
vt100_cursor_up()
{
	/* TODO: margin are not supported | scroll up are not supported */	
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_CHAR_PROP_TOUCH;
	
	vt100_cursor.row = constaint(vt100_cursor.row - param.data[0], 0, VT100_HEIGHT - 1);
}

void
vt100_cursor_down()
{
	/* TODO: margin are not supported | scroll down are not supported */
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_CHAR_PROP_TOUCH;
	
	vt100_cursor.row = constaint(vt100_cursor.row + param.data[0], 0, VT100_HEIGHT - 1);
}

void
vt100_cursor_position()
{
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_CHAR_PROP_TOUCH;
	
	vt100_cursor.row = constaint(param.data[0], 0, VT100_WIDTH - 1);
	vt100_cursor.col = constaint(param.data[1], 0, VT100_WIDTH - 1);
}

void 
vt100_cursor_restore()
{
	vt100_cursor = vt100_cursor_bkp;
}

void 
vt100_cursor_save()
{
	vt100_cursor_bkp = vt100_cursor;
}

void
vt100_cursor_down_with_scrollup()
{
	if(!(++vt100_cursor.row < VT100_WIDTH))
	{
		vt100_cursor.row = VT100_WIDTH - 1;
		vt100_buffer_shiftup();
	}
}

void
vt100_cursor_up_with_scrolldown()
{
	if(vt100_cursor.row == 0)
	{
		vt100_buffer_shiftdown();
	}
}
