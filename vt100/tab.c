#include <diy-vt100/vt100/tab.h>
#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/param.h>
#include <diy-vt100/setup.h>
#include <diy-vt100/setting.h>

/* tabulation clear */
void vt100_TBC()
{
	uint8_t i;
	
	switch(param.data[0])
	{
		case 0:
			/* clear the horizontal tab stop at the current position */
			setting_tab_low(vt100_cursor.col);
		break;

		case 3:
			/* clear all horizontal tab stops */
			setting_tabs_clear();
		break;
	}
}

/* horizontal tabulation set */
void vt100_HTS()
{
	setting_tab_high(vt100_cursor.col);
}

/* give a horizontal tab */
void vt100_HT()
{
	col_t j;
	
	for(j = vt100_cursor.col; j < VT100_WIDTH; j++)
	{
		if(setting_tab_read(j))
		{
			vt100_cursor.col = j;
		}
	}
}
