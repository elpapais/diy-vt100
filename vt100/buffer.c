#include <vt100/buffer.h>
#include <hardware/nokia1100.h>
#include <param.h>
#include <setting.h>
#include <vt100/cursor.h>

struct __vt100_char
vt100_buffer[VT100_HEIGHT][VT100_WIDTH];

/* TODO: partial support for autowarp */
void
vt100_buffer_putchar()
{
	/* show control symbol in caret notation */
	if(param.pass < ASCII_SPACE)
	{
		/* print special char */
		uint8_t tmp = param.pass;
		param.pass = '^';
		vt100_buffer_putchar();
		
		param.pass = ('@' + tmp) & ~BIT7;
	}
	
	if(!(vt100_cursor.row < VT100_HEIGHT))
	{
		vt100_buffer_shiftup();
		vt100_cursor.row = VT100_HEIGHT - 1;
		vt100_cursor.col = 0;
	}
	
	vt100_buffer[vt100_cursor.row][vt100_cursor.col].data = param.pass;
	
	vt100_buffer_prop_clear(vt100_cursor.row, vt100_cursor.col);
	
	if(setting_read(SETTING__ATTR_BOLD))
	{
		vt100_buffer_prop_high(vt100_cursor.row, vt100_cursor.col, DATA_BOLD);
	}
	
	if(setting_read(SETTING__ATTR_UNDERLINE))
	{
		vt100_buffer_prop_high(vt100_cursor.row, vt100_cursor.col, DATA_UNDERLINE);
	}
	
	if(setting_read(SETTING__ATTR_INVERSE))
	{
		vt100_buffer_prop_high(vt100_cursor.row, vt100_cursor.col, DATA_INVERSE);
	}
	
	/* TODO: blink not supported */
	vt100_buffer_row_touch(vt100_cursor.row);
	
	vt100_cursor.col++;
	
	if(!(vt100_cursor.col < VT100_WIDTH))
	{
		vt100_cursor.col = 0;
		vt100_cursor.row++;
	}
}

void
vt100_buffer_shiftup()
{
	register row_t i;
	register col_t j;
	
	/* save first row tab setting */
	for(j = 0; j < VT100_WIDTH; j++)
	{
		vt100_buffer[0][j] = vt100_buffer[1][j];
	}
	vt100_buffer_row_touch(0);
	
	/* shift up data */
	for( i = 1; i < VT100_HEIGHT - 1; i++ )
	{
		for( j = 0; j < VT100_WIDTH; j++ )
		{
			vt100_buffer[i][j] = vt100_buffer[i+1][j];
		}

		vt100_buffer_row_touch(i);
	}
	
	/* clear last row */
	for(j = 0; j < VT100_WIDTH; j++)
	{
		vt100_buffer[i][j].data = 0;
		vt100_buffer[i][j].prop = 0;
	}
	
	vt100_buffer_row_touch(i);
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
		
		vt100_buffer_row_touch(i);
	}
	
	for(j = 0; j < VT100_WIDTH; j++)
	{
		vt100_buffer[i][j].data = 0;
		vt100_buffer[i][j].prop = 0;
	}
	
	vt100_buffer_row_touch(i);
}

/* screen alignment display 
 * fill E everywhere in buffer
 */
void 
vt100_DECALN()
{
	register row_t i;
	register col_t j;
	
	for(i=0; i < VT100_HEIGHT; i++)
	{
		vt100_buffer_row_touch(i);
		
		for(j=0; j < VT100_WIDTH; j++)
		{
			vt100_buffer[i][j].data = 'E';
		}
	}
}

void vt100_ED()
{
	register row_t i;
	register col_t j;

	switch(param.data[0])
	{
		case 0:
			j=vt100_cursor.col;
			
			for(i=vt100_cursor.row; i < VT100_HEIGHT; i++)
			{
				for(; j < VT100_WIDTH; j++)
				{
					vt100_buffer[i][j].data = 0;
					vt100_buffer[i][j].prop = 0;
				}
				j = 0;
				
				vt100_buffer_row_touch(i);
			}
		break;
		
		case 1:
			
			/* Clear from top of screen to current position */
			for(i=0; i < vt100_cursor.row - 1; i++)
			{
				for(j=0; j < VT100_WIDTH; j++)
				{
					vt100_buffer[i][j].data = 0;
					vt100_buffer[i][j].prop = 0;
				}
				
				vt100_buffer_row_touch(i);
			}
		
			/* current row, coloum 0 - current col */
			for(j=0; j <= vt100_cursor.col; j++)
			{
				vt100_buffer[vt100_cursor.row][j].data = 0;
				vt100_buffer[vt100_cursor.row][j].prop = 0;
			}
			
			vt100_buffer_row_touch(i);
			
			
		break;
		
		case 2:
			/* clear the full screen */
			
			nokia1100_clear();
			
			for(i = 0; i < VT100_HEIGHT; i++)
			{
				vt100_buffer[i][0].data = 0;
				
				/* clear the double width option */
				vt100_buffer_row_low(i, ROW_DOUBLE_WIDTH);
				vt100_buffer_row_touch(i);
				
				for(j = 1; j < VT100_WIDTH; j++)
				{
					vt100_buffer[i][j].data = 0;
					vt100_buffer[i][j].prop = 0;
				}
			}
			
			vt100_cursor.col = 0;
			vt100_cursor.row = 0;
		break;
	}
}

void vt100_EL()
{
	register col_t j;

	switch(param.data[0])
	{
		case 0:
			/* current position to end of line */
			for(j=vt100_cursor.col; j < VT100_WIDTH; j++)
			{
				vt100_buffer[vt100_cursor.row][j].data = 0;
				vt100_buffer[vt100_cursor.row][j].prop = 0;
			}
			
		break;
		
		case 1:
			/* start to line to current position */
			for(j=0; j <= vt100_cursor.col; j++)
			{
				vt100_buffer[vt100_cursor.row][j].data = 0;
				vt100_buffer[vt100_cursor.row][j].prop = 0;
			}
		break;
		
		case 2:
			/* clear line */
			for(j = 0; j < VT100_WIDTH; j++)
			{
				vt100_buffer[vt100_cursor.row][j].data = 0;
				vt100_buffer[vt100_cursor.row][j].prop = 0;
			}
		break;
	}
	
	vt100_buffer_row_touch(vt100_cursor.row);
}

void
vt100_CR()
{
	vt100_cursor.col = 0;
}

void
vt100_LF()
{
	vt100_NEL();
}

void
vt100_NEL()
{
	vt100_buffer_row_touch(vt100_cursor.row);
	vt100_cursor.row++;
	
	if(!(vt100_cursor.row < VT100_HEIGHT))
	{
		vt100_buffer_shiftup();
		vt100_cursor.row = VT100_HEIGHT - 1;
	}
	
	vt100_cursor.col = 0;
}

void
vt100_buffer_copy(const struct __vt100_char buffer[VT100_HEIGHT][VT100_WIDTH])
{
	row_t i;
	col_t j;
	for(i=0; i < VT100_HEIGHT; i++)
	{
		for(j=0; j < VT100_WIDTH; j++)
		{
			vt100_buffer[i][j] = buffer[i][j];
		}
	}
	
	vt100_screen_refresh();
	vt100_buffer_row_touch(vt100_cursor.row);
}
