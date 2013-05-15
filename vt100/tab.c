#include <vt100/tab.h>

void vt100_tabulation_clear()
{
	uint8_t i;
	
	switch(vt100_param_get(0))
	{
		case 0:
			/* clear the horizontal tab stop at the current position */
			vt100.screen[0][vt100.cursor.col].tab = FALSE;
		break;

		case 3:
			/* clear all horizontal tab stops */
			for(i=0; i < VT100_WIDTH; i++)
			{
				vt100.screen[0][i].tab = FALSE;
			}
		break;
		
		//default:
			//ignored
	}
}

void vt100_set_horizontal_tabulation()
{
	vt100.screen[0][vt100.cursor.col].tab = TRUE;
}
