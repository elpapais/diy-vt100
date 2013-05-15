#include <vt100/buffer.h>

void
vt100_buffer_putchar()
{
	if(!(vt100.cursor.row < VT100_HEIGHT))
	{
		vt100_buffer_shiftup();
		vt100.cursor.row = VT100_HEIGHT - 1;
		vt100.cursor.col = 0;
	}
	
	vt100.screen[vt100.cursor.row][vt100.cursor.col].data = vt100.data;
	
	//vt100.screen[vt100.cursor.row][vt100.cursor.col].blink = vt100.mode.attr_blink;
	vt100.screen[vt100.cursor.row][vt100.cursor.col].underline = vt100.mode.attr_underline;
	vt100.screen[vt100.cursor.row][vt100.cursor.col].inverse = vt100.mode.attr_inverse;
	vt100.screen[vt100.cursor.row][vt100.cursor.col].bold = vt100.mode.attr_bold;
	
	vt100.screen[vt100.cursor.row][0].touched = 1;
	vt100.cursor.col++;
	
	if(!(vt100.cursor.col < VT100_WIDTH))
	{
		vt100.cursor.col = 0;
		vt100.cursor.row++;
	}
}

void
vt100_buffer_newrow()
{
	vt100.screen[vt100.cursor.row][0].touched = 1;
	vt100.cursor.row++;
	
	if(!(vt100.cursor.row < VT100_HEIGHT))
	{
		vt100_buffer_shiftup();
		vt100.cursor.row = VT100_HEIGHT - 1;
	}
	
	vt100.cursor.col = 0;
}

void
vt100_buffer_shiftup()
{
	row_t i;
	col_t j;
	
	for( i = 0; i < VT100_HEIGHT - 1; i++ )
	{
		for( j = 0; j < VT100_WIDTH; j++ )
		{
			vt100.screen[i][j] = vt100.screen[i+1][j];
		}
		
		vt100.screen[i][0].touched = 1;
	}
	
	vt100.screen[i][0].touched = 1;
	for( j = 0; j < VT100_WIDTH; j++ )
	{
		vt100_buffer_clear_char(i,j);
	}
}

void
vt100_buffer_shiftdown()
{
	row_t i;
	col_t j;
	
	for( i = 1; i < VT100_HEIGHT; i++ )
	{
		for( j = 0; j < VT100_WIDTH; j++ )
		{
			vt100.screen[i][j] = vt100.screen[i+1][j];
		}
		
		vt100.screen[i][0].touched = 1;
	}
	
	vt100.screen[0][0].touched = 1;
	for( j = 0; j < VT100_WIDTH; j++ )
	{
		vt100_buffer_clear_char(0,j);
	}
}

void
vt100_buffer_clear_char(const row_t i, const col_t j)
{
	vt100.screen[i][j].data = '\0';
	//vt100.screen[i][j].blink = 0;
	vt100.screen[i][j].bold = 0;
	vt100.screen[i][j].inverse = 0;
	vt100.screen[i][j].underline = 0;
}

void 
vt100_fill_all_E()
{
	row_t i;
	col_t j;
	
	for(i=0; i < VT100_HEIGHT; i++)
	{
		vt100.screen[i][0].touched = 1;
		for(j=0; j < VT100_WIDTH; j++)
		{
			vt100.screen[i][j].data = 'E';
		}
	}
}

void 
vt100_erase()
{
	row_t i;
	col_t j;

	switch(vt100_param_get(0))
	{
		case 0:
			/* clear from current position to end of line */
		
			vt100.screen[vt100.cursor.row][0].touched=1;
			for(j=vt100.cursor.col; j < VT100_WIDTH; j++)
			{
				vt100_buffer_clear_char(vt100.cursor.row, j);
			}
		break;
		
		case 1:
			/* Clear from top of screen to current position */
		
			for(i=0; i < vt100.cursor.row; i++)
			{
				vt100.screen[i][0].touched=1;
				for(j=0; j < VT100_WIDTH; j++)
				{
					vt100_buffer_clear_char(i, j);
				}
			}
			
			vt100.screen[i][0].touched=1;
			for(j=0; j <= vt100.cursor.col; j++)
			{
				vt100_buffer_clear_char(i, j);
			}
		break;
		
		case 2:
			/* clear the full screen */
			
			nokia1100_clear();
	
			for( i = 0; i < VT100_HEIGHT; i++ )
			{
				vt100.screen[i][0].touched = 1;
				
				for( j = 0; j < VT100_WIDTH; j++ )
				{
					vt100_buffer_clear_char(i,j);
				}
			}
			
			if(vt100.data == 'J')
			{
				for( i = 0; i < VT100_HEIGHT; i++ )
				{
					vt100.screen[i][0].double_width = 0;
				}
			}
			else if(vt100.data == 'K')
			{
				vt100.cursor.col=0;
				vt100.cursor.row=0;
			}
		break;
		
		//default:
			//ignore
	}
}
