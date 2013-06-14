#include <diy-vt100/vt100/attribute.h>
#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/param.h>

/* double height line [top half] */
void
vt100_DECDHL_top()
{
	/* TODO: support double height */
	vt100_buffer_row_high(vt100_cursor.row, ROW_TOUCH | ROW_DOUBLE_HEIGHT_TOP);
}

/* double height line [bottom half]*/
void
vt100_DECDHL_bottom()
{
	/* TODO: support double height */
	vt100_buffer_row_high(vt100_cursor.row, ROW_TOUCH | ROW_DOUBLE_HEIGHT_BOT);
}

/* double width line */
void 
vt100_DECDWL()
{
	/* TODO: support double width */
	vt100_buffer_row_high(vt100_cursor.row, ROW_TOUCH | ROW_DOUBLE_WIDTH);
}

/* select graphics rendition */
void 
vt100_SGR()
{
	uint8_t i;
	for(i=0; i < param.count; i++)
	{
		switch(param.data[i])
		{
			case 0:
				setting_low(SETTING__ATTR_BOLD);
				setting_low(SETTING__ATTR_INVERSE);
				setting_low(SETTING__ATTR_BLINK);
				setting_low(SETTING__ATTR_UNDERLINE);
			break;
			
			case 1:
				setting_high(SETTING__ATTR_BOLD);
			break;
			
			case 4:
				setting_high(SETTING__ATTR_UNDERLINE);
			break;
			
			case 5:
				setting_high(SETTING__ATTR_BLINK);
			break;
			
			case 7:
				setting_high(SETTING__ATTR_INVERSE);
			break;
		}
	}
}
