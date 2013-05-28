#include <vt100/screen.h>

/* must be 2^x , x>1  */
#define VT100_SCREEN_BUFFER_SIZE (NOKIA1100_WIDTH_CHAR*4)

static inline uint8_t vt100_screen_designchar(const row_t i, const col_t j, const uint8_t k);

void vt100_screen_refresh()
{
	row_t i;
	col_t j, j_max;
	uint8_t k;
	static uint8_t buffer[VT100_SCREEN_BUFFER_SIZE];
	uint8_t count;
	uint8_t data;
	
	/* generally current row has some modification, so merge cursor blink with it */
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_BUFFER_PROP_TOUCH;
	
	
	for(i=0; i < VT100_HEIGHT; i++)
	{
		/* is row modified */
		if(vt100_buffer[i][0].prop & VT100_BUFFER_PROP_TOUCH)
		{
			vt100_buffer[i][0].prop &= ~VT100_BUFFER_PROP_TOUCH;
			
			nokia1100_gotoyx(i, 0);
			
			count = 0;
			/* create a temp pointer to  vt100_screen_row_buffer[] */
			for(j=0; j < ((vt100_buffer[i][0].prop & VT100_BUFFER_PROP_DOUBLE_WIDTH) ? VT100_WIDTH/2 : VT100_WIDTH); j++)
			{
				for(k=0; k < NOKIA1100_WIDTH_CHAR; k++)
				{
					data = vt100_screen_designchar(i, j, k);
					buffer[count++] = data;
					
					if(vt100_buffer[i][0].prop & VT100_BUFFER_PROP_DOUBLE_WIDTH)
					{
						buffer[count++] = data;
					}
				}
				
				if(!(count < VT100_SCREEN_BUFFER_SIZE))
				{
					/* flush buffer */
					nokia1100_send_data(buffer, VT100_SCREEN_BUFFER_SIZE);
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
	
	if(vt100_buffer[i][j].prop & VT100_BUFFER_PROP_UNDERLINE)
	{
		send |= 0x80;
	}
	
	if(vt100_buffer[i][j].prop & VT100_BUFFER_PROP_INVERSE)
	{
		send ^= 0xFF;
	}
	
	if(j == vt100_cursor.col
		&& vt100_setting.mode & VT100_SETTING_MODE_CURSOR_STATE 
		&& i == vt100_cursor.row)
	{
		send ^= (vt100_setting.mode & VT100_SETTING_MODE_CURSOR_DESIGN) ? 0xFF : 0x80;
	}
	
	return send;
}
