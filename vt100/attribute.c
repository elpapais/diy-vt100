#include <diy-vt100/vt100/attribute.h>
#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/param.h>

rowprop_t vt100_rowprop[SCREEN_ROW];
dataprop_t vt100_dataprop;

/* double height line [top half] */
void
vt100_DECDHL_top()
{
	vt100_rowprop[vt100_cursor.row].double_height = TRUE;
	vt100_rowprop[vt100_cursor.row].double_height_pos = TRUE;
}

/* double height line [bottom half]*/
void
vt100_DECDHL_bottom()
{
	vt100_rowprop[vt100_cursor.row].double_height = TRUE;
	vt100_rowprop[vt100_cursor.row].double_height_pos = FALSE;
}

/* double width line */
void 
vt100_DECDWL()
{
	vt100_rowprop[vt100_cursor.row].double_width = TRUE;
}

/* select graphics rendition */
void 
vt100_SGR()
{
	for(uint8_t i=0; i < param.count; i++)
	{
		switch(param.data[i])
		{
			case 0:
				vt100_dataprop.bold = FALSE;
				vt100_dataprop.invert = FALSE;
				vt100_dataprop.blink = FALSE;
				vt100_dataprop.underline = FALSE;
			break;
			
			case 1:
				vt100_dataprop.bold = TRUE;
			break;
			
			case 4:
				vt100_dataprop.underline = TRUE;
			break;
			
			case 5:
				vt100_dataprop.blink = TRUE;
			break;
			
			case 7:
				vt100_dataprop.invert = TRUE;
			break;
		}
	}
}
