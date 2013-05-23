#include <vt100/tab.h>

void vt100_tabulation_clear()
{
	uint8_t i;
	
	switch(vt100_param.data[0])
	{
		case 0:
			/* clear the horizontal tab stop at the current position */
			vt100_buffer[0][vt100_cursor.col].prop &= VT100_BUFFER_PROP_TAB;
		break;

		case 3:
			/* clear all horizontal tab stops */
			for(i=0; i < VT100_WIDTH; i++)
			{
				vt100_buffer[0][i].prop &= VT100_BUFFER_PROP_TAB;
			}
		break;
		
		//default:
			//ignored
	}
}

void vt100_tabulation_set()
{
	vt100_buffer[0][vt100_cursor.col].prop |= VT100_BUFFER_PROP_TAB;
}

void vt100_tabulation_goto_next()
{
	register col_t j;
	
	for(j = vt100_cursor.col; j < VT100_WIDTH; j++)
	{
		if(vt100_buffer[0][j].prop & VT100_BUFFER_PROP_TAB)
		{
			vt100_cursor.col = j;
			break;
		}
	}
}
