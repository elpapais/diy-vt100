#include <vt100/tab.h>
#include <vt100/buffer.h>
#include <vt100/cursor.h>
#include <param.h>
#include <setup.h>

/* tabulation clear */
void vt100_TBC()
{
	uint8_t i;
	
	switch(param.data[0])
	{
		case 0:
			/* clear the horizontal tab stop at the current position */
			vt100_buffer[0][vt100_cursor.col].prop &= VT100_CHAR_PROP_TAB;
		break;

		case 3:
			/* clear all horizontal tab stops */
			for(i=0; i < VT100_WIDTH; i++)
			{
				vt100_buffer[0][i].prop &= VT100_CHAR_PROP_TAB;
			}
		break;
		
		//default:
			//ignored
	}
}

/* horizontal tabulation set */
void vt100_HTS()
{
	vt100_buffer[0][vt100_cursor.col].prop |= VT100_CHAR_PROP_TAB;
}

/* give a horizontal tab */
void vt100_HT()
{
	register col_t j;
	
	for(j = vt100_cursor.col; j < VT100_WIDTH; j++)
	{
		if(vt100_buffer[0][j].prop & VT100_CHAR_PROP_TAB)
		{
			vt100_cursor.col = j;
			break;
		}
	}
}
