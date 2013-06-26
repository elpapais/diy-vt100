#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/param.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/vt100/attribute.h>

/* TODO: partial support for autowarp */
void
vt100_putch(const uint8_t data)
{
	/* show control symbol in caret notation */
	if(data < ASCII_SPACE)
	{
		/* print special char */
		vt100_putch('^');
		vt100_putch('@' + data);
		
		return;
	}
	
	/* screen function have no tension of screen overflow */
	
	screen_putch(data, vt100_dataprop);
	
	/* increment position */
	vt100_cursor.col++;

	if(parm_setting.bits.DECAWM)
	{
		/* screen overflow on right */
		if(!(vt100_cursor.col < SCREEN_COL))
		{
			vt100_cursor.col = 0;
			vt100_cursor.row++;
		}
		
		/* screen overflowed on bottom */
		if(!(vt100_cursor.row < SCREEN_ROW))
		{
			screen_shiftup();
		
			vt100_cursor.row = SCREEN_ROW - 1;
			vt100_cursor.col = 0;
		}
	}
	else if(!(vt100_cursor.col < SCREEN_COL))
	{
		vt100_cursor.col = SCREEN_COL - 1;
	}
}

/* screen alignment display 
 * fill E everywhere
 */
void 
vt100_DECALN()
{
	screen_full_E();
}

void vt100_ED()
{
	switch(param.data[0])
	{
		case 0:
			/* Clear from current position to end of screen */
			screen_segment_clear(vt100_cursor.row, vt100_cursor.col, SCREEN_COL - 1);
			
			for(register row_t i=vt100_cursor.row; i < SCREEN_ROW; i++)
			{
				screen_row_clear(i);
			}
		break;
		
		case 1:
			
			/* Clear from top of screen to current position */
			
			
			for(register row_t i=0; i < (vt100_cursor.row - 1); i++)
			{
				screen_row_clear(i);
			}
			
			screen_segment_clear(vt100_cursor.row, vt100_cursor.col, SCREEN_COL - 1);
			
		break;
		
		case 2:
			/* clear the full screen */
			
			screen_full_clear();
			
			vt100_cursor.col = 0;
			vt100_cursor.row = 0;
		break;
	}
}

void vt100_EL()
{
	switch(param.data[0])
	{
		case 0:
			/* current position to end of line */
			screen_segment_clear(vt100_cursor.row, vt100_cursor.col, (SCREEN_COL - 1));
			
		break;
		
		case 1:
			/* start to line to current position */
			screen_segment_clear(vt100_cursor.row, 0, vt100_cursor.col);
		break;
		
		case 2:
			/* clear line */
			screen_row_clear(vt100_cursor.row);
		break;
	}
}

/* \n */
void
vt100_LF()
{
	vt100_cursor.row++;
	
	if(!(vt100_cursor.row < SCREEN_ROW))
	{
		screen_shiftup();
		vt100_cursor.row = SCREEN_ROW - 1;
	}
	
	if(setting.bits.LNM)
	{
		vt100_cursor.col = 0;
	}
}

/* \r */
void
vt100_CR()
{
	vt100_cursor.col = 0;
}

void
vt100_NEL()
{
	vt100_cursor.row++;
	
	if(!(vt100_cursor.row < SCREEN_ROW))
	{
		screen_shiftup();
		vt100_cursor.row = SCREEN_ROW - 1;
	}
	
	vt100_cursor.col = 0;
}
