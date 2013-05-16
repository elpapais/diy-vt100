#include <vt100/screen.h>

void
vt100_refresh()
{
	row_t i;
	col_t j;
	
	for(i=0; i < VT100_HEIGHT; i++)
	{
		if(vt100.screen[i][0].touched)
		{
			nokia1100_gotoyx(i, 0);
			
			vt100.screen[i][0].touched = FALSE;
			
			for(j=0; j < (vt100.screen[i][0].double_width ? VT100_WIDTH/2 : VT100_WIDTH); j++)
			{
				vt100_print_char(i, j, FALSE);
			}
		}
	}
}

void vt100_print_char(row_t i, col_t j, bool_t has_cursor)
{
	uint8_t k;
	uint8_t send, tmp;
	
	for(k=0; k < NOKIA1100_WIDTH_CHAR; k++)
	{
		send = font_simple_get(vt100.screen[i][j].data, k);
		
		if(vt100.screen[i][j].inverse)
		{
			send ^= 0xFF;
		}
		
		if(vt100.screen[i][j].underline)
		{
			send ^= 0x80;
		}
		
		if(vt100.screen[i][0].double_height_top)
		{
			tmp = send;
			send = 0x00;
			if(tmp & BIT3)
			{
				send |= BIT7 | BIT6;
			}
			
			if(tmp & BIT2)
			{
				send |= BIT5 | BIT4;
			}
			
			if(tmp & BIT1)
			{
				send |= BIT3 | BIT2;
			}
			
			if(tmp & BIT0)
			{
				send |= BIT1 | BIT0;
			}
		}
		else if(vt100.screen[i][0].double_height_bottom)
		{
			tmp = send;
			send = 0x00;
			if(tmp & BIT7)
			{
				send |= BIT1 | BIT0;
			}
			
			if(tmp & BIT6)
			{
				send |= BIT3 | BIT2;
			}
			
			if(tmp & BIT5)
			{
				send |= BIT5 | BIT4;
			}
			
			if(tmp & BIT4)
			{
				send |= BIT7 | BIT6;
			}
		}
		
		if(has_cursor)
		{
			send ^= 0x80;
		}
		
		if(vt100.screen[i][0].double_width)
		{
			nokia1100_send_data(send);
		}
		
		nokia1100_send_data(send);
	}
}
