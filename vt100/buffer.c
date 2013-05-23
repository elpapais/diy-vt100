#include <vt100/buffer.h>

struct __vt100_char
vt100_buffer[VT100_HEIGHT][VT100_WIDTH];

void
vt100_buffer_putchar()
{
	if(vt100_param.pass < ASCII_SPACE)
	{
		/* print special char */
		uint8_t tmp = vt100_param.pass;
		vt100_param.pass = '^';
		vt100_buffer_putchar();
		vt100_param.pass = 'A'+ 1 + tmp ;
	}
	
	if(!(vt100_cursor.row < VT100_HEIGHT))
	{
		vt100_buffer_shiftup();
		vt100_cursor.row = VT100_HEIGHT - 1;
		vt100_cursor.col = 0;
	}
	
	vt100_buffer[vt100_cursor.row][vt100_cursor.col].data = vt100_param.pass;
	
	vt100_buffer[vt100_cursor.row][vt100_cursor.col].prop = 0;
	
	if(vt100_setting.mode & VT100_SETTING_MODE_ATTR_BOLD)
	{
		vt100_buffer[vt100_cursor.row][vt100_cursor.col].prop |= VT100_BUFFER_PROP_BOLD;
	}
	
	if(vt100_setting.mode & VT100_SETTING_MODE_ATTR_UNDERLINE)
	{
		vt100_buffer[vt100_cursor.row][vt100_cursor.col].prop |= VT100_BUFFER_PROP_UNDERLINE;
	}
	
	if(vt100_setting.mode & VT100_SETTING_MODE_ATTR_INVERSE)
	{
		vt100_buffer[vt100_cursor.row][vt100_cursor.col].prop |= VT100_BUFFER_PROP_INVERSE;
	}
	
	/* TODO: blink not supported */
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_BUFFER_PROP_TOUCH;
	
	vt100_cursor.col++;
	
	if(!(vt100_cursor.col < VT100_WIDTH))
	{
		vt100_cursor.col = 0;
		vt100_cursor.row++;
	}
}

void
vt100_buffer_newrow()
{
	vt100_buffer[vt100_cursor.row][0].prop |= VT100_BUFFER_PROP_TOUCH;
	vt100_cursor.row++;
	
	if(!(vt100_cursor.row < VT100_HEIGHT))
	{
		vt100_buffer_shiftup();
		vt100_cursor.row = VT100_HEIGHT - 1;
	}
	
	vt100_cursor.col = 0;
}

void
vt100_buffer_shiftup()
{
	register row_t i;
	register col_t j;
	
	for( i = 0; i < VT100_HEIGHT - 1; i++ )
	{
		for( j = 0; j < VT100_WIDTH; j++ )
		{
			vt100_buffer[i][j] = vt100_buffer[i+1][j];
		}

		vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
	}
	
	vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
	
	for( j = 0; j < VT100_WIDTH; j++ )
	{
		vt100_buffer_clear_char(i,j);
	}
}

void
vt100_buffer_shiftdown()
{
	register row_t i;
	register col_t j;
	
	for(i = 1; i < VT100_HEIGHT; i++)
	{
		for(j = 0; j < VT100_WIDTH; j++)
		{
			vt100_buffer[i][j] = vt100_buffer[i-1][j];
		}
		
		vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
	}
	
	vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
	
	for(i=0,j = 0; j < VT100_WIDTH; j++)
	{
		vt100_buffer_clear_char(i,j); /*(0,j)*/
	}
}

void
vt100_buffer_clear_char(const register row_t i, const register col_t j)
{
	vt100_buffer[i][j].data = '\0';
	vt100_buffer[i][j].prop = 0;
}

void 
vt100_buffer_fill_E()
{
	register row_t i;
	register col_t j;
	
	for(i=0; i < VT100_HEIGHT; i++)
	{
		vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
		
		for(j=0; j < VT100_WIDTH; j++)
		{
			vt100_buffer[i][j].data = 'E';
		}
	}
}

void 
vt100_buffer_erase()
{
	register row_t i;
	register col_t j;

	switch(vt100_param.data[0])
	{
		case 0:
			/* clear from current position to end of line */
		
			vt100_buffer[vt100_cursor.row][0].prop |= VT100_BUFFER_PROP_TOUCH;
			
			for(j=vt100_cursor.col; j < VT100_WIDTH; j++)
			{
				vt100_buffer_clear_char(vt100_cursor.row, j);
			}
		break;
		
		case 1:
			/* Clear from top of screen to current position */
		
			for(i=0; i < vt100_cursor.row; i++)
			{
				vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
				
				for(j=0; j < VT100_WIDTH; j++)
				{
					vt100_buffer_clear_char(i, j);
				}
			}
			
			vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
			
			for(j=0; j <= vt100_cursor.col; j++)
			{
				vt100_buffer_clear_char(i, j);
			}
		break;
		
		case 2:
			/* clear the full screen */
			
			nokia1100_clear();
	
			register uint8_t cleardw;
			
			/* clear the double width option */
			cleardw = vt100_param.pass == 'J' ? ~VT100_BUFFER_PROP_DOUBLE_WIDTH : VT100_BUFFER_PROP_DOUBLE_WIDTH;
	
			for( i = 0; i < VT100_HEIGHT; i++ )
			{
				vt100_buffer[i][0].prop &= cleardw;
				
				vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
				
				for( j = 0; j < VT100_WIDTH; j++ )
				{
					vt100_buffer_clear_char(i,j);
				}
			}
			
			if(vt100_param.pass == 'K')
			{
				vt100_cursor.col = 0;
				vt100_cursor.row = 0;
			}
		break;
		
		//default:
			//ignore
	}
}
