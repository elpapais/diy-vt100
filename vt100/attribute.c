#include <vt100/attribute.h>
#include <vt100/buffer.h>
#include <vt100/misc.h>
#include <vt100/cursor.h>
#include <param.h>

void
vt100_double_height_tophalf()
{
	/* TODO: support double height */
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_CHAR_PROP_TOUCH | VT100_CHAR_PROP_DOUBLE_HEIGHT_TOP;
}

void
vt100_double_height_bottomhalf()
{
	/* TODO: support double height */
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_CHAR_PROP_TOUCH | VT100_CHAR_PROP_DOUBLE_HEIGHT_BOTTOM;
}

void 
vt100_double_width()
{
	/* TODO: support double width */
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_CHAR_PROP_TOUCH | VT100_CHAR_PROP_DOUBLE_WIDTH;
}

void 
vt100_attribute_select()
{
	uint8_t i;
	for(i=0; i < param.count; i++)
	{
		switch(param.data[i])
		{
			case 0:
				vt100_setting &= ~(VT100_SETTING_ATTR_BOLD | 
										VT100_SETTING_ATTR_INVERSE | 
										VT100_SETTING_ATTR_BLINK | 
										VT100_SETTING_ATTR_UNDERLINE);
			break;
			
			case 1:
				vt100_setting |= VT100_SETTING_ATTR_BOLD;
			break;
			
			case 4:
				vt100_setting |= VT100_SETTING_ATTR_UNDERLINE;
			break;
			
			case 5:
				vt100_setting |= VT100_SETTING_ATTR_BLINK;
			break;
			
			case 7:
				vt100_setting |= VT100_SETTING_ATTR_INVERSE;
			break;
			
			//default:
				//ignored
		}
	}
}
