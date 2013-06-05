#include <vt100/tab.h>
#include <vt100/buffer.h>
#include <vt100/cursor.h>
#include <param.h>
#include <setup.h>
#include <setting.h>

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
			setting_tab_clearall();
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
