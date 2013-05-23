#include <vt100/cursor.h>

struct __vt100_cursor vt100_cursor;

void
vt100_cursor_backward()
{
	/* TODO: margin are not supported */
	vt100_cursor.col = constaint(vt100_cursor.col - vt100_param.data[0], 0, VT100_WIDTH - 1);
}

void
vt100_cursor_forward()
{
	/* TODO: margin are not supported */
	vt100_cursor.col = constaint(vt100_cursor.col + vt100_param.data[0], 0, VT100_WIDTH - 1);
}

void
vt100_cursor_up()
{
	/* TODO: margin are not supported | scroll up are not supported */	
	vt100_cursor.row = constaint(vt100_cursor.row - vt100_param.data[0], 0, VT100_HEIGHT - 1);
}

void
vt100_cursor_down()
{
	/* TODO: margin are not supported | scroll down are not supported */
	vt100_cursor.row = constaint(vt100_cursor.row + vt100_param.data[0], 0, VT100_HEIGHT - 1);
}

void
vt100_cursor_position()
{
	vt100_cursor.row = constaint(vt100_param.data[0], 0, VT100_WIDTH - 1);
	vt100_cursor.col = constaint(vt100_param.data[1], 0, VT100_WIDTH - 1);
}

void 
vt100_cursor_restore()
{
	vt100_cursor = vt100_setting.cursor_bkp;
}

void 
vt100_cursor_save()
{
	vt100_setting.cursor_bkp = vt100_cursor;
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

void
vt100_cursor_draw()
{
	/* make sure we dont overflow the cursor */
	if((vt100_buffer[vt100_cursor.row][0].prop & VT100_BUFFER_PROP_DOUBLE_WIDTH) && vt100_cursor.col > VT100_WIDTH/2)
	{
		vt100_cursor.col /=2;
	}
	
	nokia1100_gotoyx(vt100_cursor.row, vt100_cursor.col * NOKIA1100_WIDTH_CHAR);
	
	vt100_screen_printchar(vt100_cursor.row, vt100_cursor.col, (vt100_setting.mode | VT100_SETTING_MODE_CURSOR_STATE));
}
