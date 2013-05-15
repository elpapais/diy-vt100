#include <vt100/attribute.h>

void vt100_set_doubleheight_tophalf()
{
	/* TODO: support double height */
	vt100.screen[vt100.cursor.row][0].double_height_top=1;
}

void vt100_set_doubleheight_bottomhalf()
{
	/* TODO: support double height */
	vt100.screen[vt100.cursor.row][0].double_height_bottom=1;
}

void 
vt100_set_doublewidth()
{
	/* TODO: support double width */
	vt100.screen[vt100.cursor.row][0].double_width=1;
}

void 
vt100_select_attribute()
{
	uint8_t i;
	for(i=0; i < vt100_param_getcount(); i++)
	{
		
		switch(vt100_param_get(i))
		{
			case 0:
				vt100.mode.attr_bold=0;
				vt100.mode.attr_blink=0;
				vt100.mode.attr_inverse=0;
				vt100.mode.attr_underline=0;
			break;
			
			case 1:
				vt100.mode.attr_bold=1;
			break;
			
			case 4:
				vt100.mode.attr_underline=1;
			break;
			
			case 5:
				vt100.mode.attr_blink=1;
			break;
			
			case 7:
				vt100.mode.attr_inverse=1;
			break;
			
			//default:
				//ignored
		}
	}
}
