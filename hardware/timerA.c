#include <hardware/timerA.h>

void timerA_init()
{
	TACTL = TASSEL_2 + ID_3  + MC_1;
	
	/* A0 */
	TACCR0 = 0xFFFF;
	TACCTL0 = CCIE;
	
	/* interrupt goes to timerA0_interrupt() @ 7Hz */
	
	/* A1 */
	TACCR1 = 1;
	TACCTL1 = CCIE;
	
	/* interrupt goes to timerA1_interrupt() @ 500KHz */
}

/* cursor blinking */
void timerA0_interrupt()
{
	/* make sure we dont overflow the cursor */
	if(vt100.screen[vt100.cursor.row][0].double_width && vt100.cursor.col > VT100_WIDTH/2)
	{
		vt100.cursor.col /=2;
	}
	
	nokia1100_gotoyx(vt100.cursor.row, vt100.cursor.col * NOKIA1100_WIDTH_CHAR);
	
	vt100_print_char(vt100.cursor.row, vt100.cursor.col, vt100.mode.cursor_state);
	
	vt100.mode.cursor_state ^= TRUE;
}

void timerA1_interrupt()
{
	if(TACCTL1 & CCIFG)
	{
		/* received uart data */
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
