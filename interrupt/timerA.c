#include <interrupt/timerA.h>

void timerA_init()
{
	/* A0 */
	TA0CCR0 = 0xFFFF;
	TACCTL0 = CCIE;
	TACTL = TASSEL_2 + ID_3  + MC_1;
	
	/* interrupt goes to timerA0_interrupt() @ 6Hz */
	
	/* A1 */
	TACCR1 = 1;
	TACCTL1 = CCIE;
	
	/* interrupt goes to timerA1_interrupt() @ 500Khz */
}

void timerA1_interrupt()
{
	if(TACCTL1 & CCIFG)
	{
		/* pop data from keyboard and push to uart_cqueue_tx */
		while(cqueue_count(keyboard_ps2.queue))
		{
			//uart_send(keyboard_ps2_data_decode(cqueue_pop(&keyboard_ps2.queue)));
			vt100.data = keyboard_ps2_data_decode(cqueue_pop(&keyboard_ps2.queue));
			
			if(vt100.data)
			{
				control();
			}
		}
		
		/* do the work */
		while(cqueue_count(uart_cqueue_rx))
		{
			vt100.data = cqueue_pop(&uart_cqueue_rx);
			control();
		}
		
		vt100_refresh();
		
		/* clear the interrupt flag */
		TACCTL1 &= ~CCIFG;
	}
}

void timerA0_interrupt()
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
