#include <hardware/nokia1100.h>
#include <hardware/flash.h>

#include <vt100/screen.h>
#include <vt100/misc.h>
#include <vt100/buffer.h>
#include <vt100/cursor.h>

#include <font/simple.h>
#include <setting.h>

/* must be 2^x , x>1, x <= VT100_WIDTH  */
#define VT100_SCREEN_BUFFER_SIZE (NOKIA1100_WIDTH_CHAR*4)

static inline uint8_t vt100_screen_designchar(const row_t i, const col_t j, const uint8_t k);
static uint8_t screen_buffer[VT100_SCREEN_BUFFER_SIZE];

void vt100_screen_refresh()
{
	row_t i;
	col_t j, j_max;
	uint8_t k;
	
	uint8_t count;
	uint8_t data;
	
	/* generally current row has some modification, so merge cursor blink with it */
	vt100_buffer_row_touch(vt100_cursor.row);
	
	for(i=0; i < VT100_HEIGHT; i++)
	{
		/* is row modified */
		if(vt100_buffer_row_touched(i))
		{
			vt100_buffer[i][0].prop &= ~ROW_TOUCH;
			
			nokia1100_gotoyx(i, 0);
			
			count = 0;
			/* create a temp pointer to  vt100_screen_row_buffer[] */
			for(j=0; j < (vt100_buffer_row_read(i, ROW_DOUBLE_WIDTH) ? VT100_WIDTH/2 : VT100_WIDTH); j++)
			{
				for(k=0; k < NOKIA1100_WIDTH_CHAR; k++)
				{
					data = vt100_screen_designchar(i, j, k);
					screen_buffer[count++] = data;
					
					if(vt100_buffer_row_read(i, ROW_DOUBLE_WIDTH))
					{
						screen_buffer[count++] = data;
					}
				}
				
				if(!(count < VT100_SCREEN_BUFFER_SIZE))
				{
					/* flush buffer */
					nokia1100_send_data(screen_buffer, VT100_SCREEN_BUFFER_SIZE);
					count = 0;
				}
			}
		}
	}
}

static inline uint8_t vt100_screen_designchar(const row_t i, const col_t j, const uint8_t k)
{
	uint8_t send, tmp;
	
	/* design the char */
	send = font_simple_get(vt100_buffer[i][j].data, k);
	
	if(vt100_buffer_row_read(i, ROW_DOUBLE_HEIGHT_TOP))
	{
		tmp = send;
		send = 0x00;
		if(__read(tmp,BIT3))
		{
			__high(send, BIT7|BIT6);
		}
		
		if(__read(tmp,BIT2))
		{
			__high(send, BIT5|BIT4);
		}
		
		if(__read(tmp,BIT1))
		{
			__high(send, BIT3|BIT2);
		}
		
		if(__read(tmp,BIT0))
		{
			__high(send, BIT1|BIT0);
		}
	}
	else if(__read(vt100_buffer[i][0].prop, ROW_DOUBLE_HEIGHT_BOT))
	{
		tmp = send;
		send = 0x00;
		
		if(__read(tmp,BIT4))
		{
			__high(send, BIT1|BIT0);
		}
		
		if(__read(tmp,BIT5))
		{
			__high(send, BIT3|BIT2);
		}
		
		if(__read(tmp,BIT6))
		{
			__high(send, BIT5|BIT4);
		}
		
		if(__read(tmp,BIT7))
		{
			__high(send, BIT7|BIT6);
		}
	}
	
	if(vt100_buffer_prop_read(i,j,DATA_UNDERLINE))
	{
		send |= 0x80;
	}
	
	if(vt100_buffer_prop_read(i,j,DATA_INVERSE))
	{
		send ^= 0xFF;
	}
	
	if(j == vt100_cursor.col
		&& setting_read(SETTING__CURSOR_STATE) 
		&& i == vt100_cursor.row)
	{
		send ^= flash_setting_read(SETTING_CURSOR) ? 0xFF : 0x80;
	}
	
	return send;
}
