#include <vt100/screen.h>

void
vt100_screen_refresh()
{
	register row_t i;
	register col_t j;
	
	for(i=0; i < VT100_HEIGHT; i++)
	{
		if(vt100_buffer[i][0].prop & VT100_BUFFER_PROP_TOUCH)
		{
			nokia1100_gotoyx(i, 0);
			
			vt100_buffer[i][0].prop &= ~VT100_BUFFER_PROP_TOUCH;
			
			for(j=0; j < ((vt100_buffer[i][0].prop & VT100_BUFFER_PROP_DOUBLE_WIDTH) ? VT100_WIDTH/2 : VT100_WIDTH); j++)
			{
				vt100_screen_printchar(i, j, FALSE);
			}
		}
	}
}

void vt100_screen_printchar(register row_t i, register col_t j, register bool_t has_cursor)
{
	register uint8_t k;
	uint8_t send, tmp;
	
	for(k=0; k < NOKIA1100_WIDTH_CHAR; k++)
	{
		send = font_simple_get(vt100_buffer[i][j].data, k);
		
		if(vt100_buffer[i][0].prop & VT100_BUFFER_PROP_DOUBLE_HEIGHT_TOP)
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
		else if(vt100_buffer[i][0].prop & VT100_BUFFER_PROP_DOUBLE_HEIGHT_BOTTOM)
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
		
		if(vt100_buffer[i][j].prop & VT100_BUFFER_PROP_INVERSE)
		{
			send ^= 0xFF;
		}
		
		if(vt100_buffer[i][j].prop & VT100_BUFFER_PROP_UNDERLINE)
		{
			send ^= 0x80;
		}
		
		if(vt100_buffer[i][0].prop & VT100_BUFFER_PROP_DOUBLE_WIDTH)
		{
			nokia1100_send_data(send);
		}
		
		nokia1100_send_data(send);
	}
}
