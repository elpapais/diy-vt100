#include <vt100/cursor.h>

void
vt100_cursor()
{
	/* timer A1 at 15.625 KHz, we need to produce delay for blinking cursor */
	//TA0CCR0 = 100;//7812;
	TA0CCTL0 = CCIE;
	TA0CTL = TASSEL_2 + ID_3  + MC_2;
}

/* using Watchdog Interval Timer interrupt service for cursor blinking */
void timer0_interrupt()
{
	/* make sure we dont overflow the cursor */
	if(vt100.screen[vt100.cursor.row][0].double_width && vt100.cursor.col > VT100_WIDTH/2)
	{
		vt100.cursor.col /=2;
	}
	
	nokia1100_gotoyx(vt100.cursor.row, vt100.cursor.col * NOKIA1100_WIDTH_CHAR);
	if(vt100.mode.cursor_state)
	{
		vt100_print_char(vt100.cursor.row, vt100.cursor.col, TRUE);
	}
	else
	{
		/* overwrite the previous text to show like blinking */
		vt100_print_char(vt100.cursor.row, vt100.cursor.col, FALSE);
	}
	
	vt100.mode.cursor_state = ! vt100.mode.cursor_state;
}

void
vt100_cursor_backward()
{
	/* TODO: margin are not supported */
	vt100.cursor.col = constaint(vt100.cursor.col - vt100_param_get(0), 0, VT100_WIDTH - 1);
}

void
vt100_cursor_forward()
{
	/* TODO: margin are not supported */
	vt100.cursor.col = constaint(vt100.cursor.col + vt100_param_get(0), 0, VT100_WIDTH - 1);
}

void
vt100_cursor_up()
{
	/* TODO: margin are not supported | scroll up are not supported */	
	vt100.cursor.row = constaint(vt100.cursor.row - vt100_param_get(0), 0, VT100_WIDTH - 1);
}

void
vt100_cursor_down()
{
	/* TODO: margin are not supported | scroll down are not supported */
	vt100.cursor.row = constaint(vt100.cursor.row + vt100_param_get(0), 0, VT100_WIDTH - 1);
}

void
vt100_cursor_position()
{
	vt100.cursor.row = constaint(vt100_param_get(0), 0, VT100_WIDTH - 1);
	vt100.cursor.col = constaint(vt100_param_get(1), 0, VT100_WIDTH - 1);
}


void 
vt100_restore_cursor()
{
	vt100.cursor = vt100.mode.cursor_bkp;
}

void 
vt100_save_cursor()
{
	vt100.mode.cursor_bkp = vt100.cursor;
}

void
vt100_cursor_down_with_scrollup()
{
	if(!(++vt100.cursor.row < VT100_WIDTH))
	{
		vt100.cursor.row = VT100_WIDTH - 1;
		vt100_buffer_shiftup();
	}
}


void
vt100_cursor_up_with_scrolldown()
{
	if(vt100.cursor.row == 0)
	{
		vt100_buffer_shiftdown();
	}
}
