#include <vt100/attribute.h>

void vt100_set_doubleheight_tophalf()
{
	
	/* TODO: support double height */
	vt100.screen[vt100.cursor.row][0].touched = TRUE;
	vt100.screen[vt100.cursor.row][0].double_height_top = TRUE;
}

void vt100_set_doubleheight_bottomhalf()
{
	/* TODO: support double height */
	vt100.screen[vt100.cursor.row][0].touched = TRUE;
	vt100.screen[vt100.cursor.row][0].double_height_bottom = TRUE;
}

void 
vt100_set_doublewidth()
{
	/* TODO: support double width */
	vt100.screen[vt100.cursor.row][0].touched = TRUE;
	vt100.screen[vt100.cursor.row][0].double_width = TRUE;
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
				vt100.mode.attr_bold = FALSE;
				vt100.mode.attr_blink = FALSE;
				vt100.mode.attr_inverse = FALSE;
				vt100.mode.attr_underline = FALSE;
			break;
			
			case 1:
				vt100.mode.attr_bold = TRUE;
			break;
			
			case 4:
				vt100.mode.attr_underline = TRUE;
			break;
			
			case 5:
				vt100.mode.attr_blink = TRUE;
			break;
			
			case 7:
				vt100.mode.attr_inverse = TRUE;
			break;
			
			//default:
				//ignored
		}
	}
}
