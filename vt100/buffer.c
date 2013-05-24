#include <vt100/buffer.h>

struct __vt100_char
vt100_buffer[VT100_HEIGHT][VT100_WIDTH];

/* TODO: partial support for autowarp */
void
vt100_buffer_putchar()
{
	/* show control symbol in caret notation */
	if(vt100_param.pass < ASCII_SPACE)
	{
		/* print special char */
		uint8_t tmp = vt100_param.pass;
		vt100_param.pass = '^';
		vt100_buffer_putchar();
		
		vt100_param.pass = ('@' + tmp) & ~BIT7;
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
	uint8_t prop;
	
	/* save first row tab setting */
	for(j = 0; j < VT100_WIDTH; j++)
	{
		prop = vt100_buffer[0][j].prop;
		vt100_buffer[0][j] = vt100_buffer[1][j];
		
		if(prop & VT100_BUFFER_PROP_TAB)
		{
			vt100_buffer[0][j].prop |= VT100_BUFFER_PROP_TAB;
		}
		else
		{
			vt100_buffer[0][j].prop &= ~VT100_BUFFER_PROP_TAB;
		}
	}
	vt100_buffer[0][0].prop |= VT100_BUFFER_PROP_TOUCH;
	
	/* shift up data */
	for( i = 1; i < VT100_HEIGHT - 1; i++ )
	{
		for( j = 0; j < VT100_WIDTH; j++ )
		{
			vt100_buffer[i][j] = vt100_buffer[i+1][j];
		}

		vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
	}
	
	/* clear last row */
	for(j = 0; j < VT100_WIDTH; j++)
	{
		vt100_buffer[i][j].data = 0;
		vt100_buffer[i][j].prop = 0;
	}
	
	vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
}

void
vt100_buffer_shiftdown()
{
	register row_t i;
	register col_t j;
	
	for(i = VT100_HEIGHT - 1; i > 0; i--)
	{
		for(j = 0; j < VT100_WIDTH; j++)
		{
			vt100_buffer[i][j] = vt100_buffer[i-1][j];
		}
		
		vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
	}
	
	for(j = 0; j < VT100_WIDTH; j++)
	{
		vt100_buffer[i][j].data = 0;
		vt100_buffer[i][j].prop &= VT100_BUFFER_PROP_TAB;
	}
	
	vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
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
			
			for(j=vt100_cursor.col; j < VT100_WIDTH; j++)
			{
				vt100_buffer[vt100_cursor.row][j].data = 0;
				vt100_buffer[vt100_cursor.row][j].prop &= VT100_BUFFER_PROP_TAB;
			}
			
			vt100_buffer[vt100_cursor.row][0].prop |= VT100_BUFFER_PROP_TOUCH;
			
			if(vt100_param.pass == 'J')
			{
				/* clear from (current position row + 1) to end of screen */
				
				for(i=vt100_cursor.row + 1; i < VT100_HEIGHT; i++)
				{
					for(j=0; j < VT100_WIDTH; j++)
					{
						vt100_buffer[i][j].data = 0;
						vt100_buffer[i][j].prop = 0;
					}
					
					vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
				}
			}
		break;
		
		case 1:
			/* Clear from top of screen to current position */
		
			for(i=0; i < vt100_cursor.row; i++)
			{
				for(j=0; j < VT100_WIDTH; j++)
				{
					vt100_buffer[i][j].data = 0;
					vt100_buffer[i][j].prop &= VT100_BUFFER_PROP_TAB;
				}
				
				vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
			}
			
			/* current row, coloum 0 - current col */
			for(j=0; j <= vt100_cursor.col; j++)
			{
				vt100_buffer[i][j].data = 0;
				vt100_buffer[i][j].prop &= VT100_BUFFER_PROP_TAB;
			}
			
			vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
		break;
		
		case 2:
			/* clear the full screen */
			
			nokia1100_clear();
	
			register uint8_t clearprop;
			
			/* clear the double width option */
			clearprop = (vt100_param.pass == 'J' ? 
							~(VT100_BUFFER_PROP_BOLD | VT100_BUFFER_PROP_INVERSE | VT100_BUFFER_PROP_UNDERLINE | VT100_BUFFER_PROP_DOUBLE_WIDTH) : 
							~(VT100_BUFFER_PROP_BOLD | VT100_BUFFER_PROP_INVERSE | VT100_BUFFER_PROP_UNDERLINE));

			for(i = 0; i < VT100_HEIGHT; i++)
			{
				vt100_buffer[i][0].data = 0;
				vt100_buffer[i][0].prop &= clearprop;
				vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
				
				for(j = 1; j < VT100_WIDTH; j++)
				{
					vt100_buffer[i][j].data = 0;
					vt100_buffer[i][j].prop &= VT100_BUFFER_PROP_TAB;
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
