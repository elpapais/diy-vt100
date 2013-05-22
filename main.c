#include <msp430.h>
#include <common.h>
#include <splash.h>
#include <vt100/vt100.h>
#include <hardware/timerA.h>
#include <hardware/usci0.h>
#include <hardware/port2.h>

void msp430_init();

int
main()
{
	register uint8_t data;
	msp430_init();
	port1_init();
	vt100_init();
	
	splash();
	
	usci0_init();
	timerA_init();
	port2_init();

	while(TRUE)
	{
		_BIS_SR(LPM1_bits + GIE);
		
		/* screen refresh { */
		while(cqueue_count(uart_cqueue_rx))
		{
			vt100.data = cqueue_pop(&uart_cqueue_rx);
			control();
		}
		
		vt100_refresh();
		/* } */
		
		/* cursor blinking { */
		/* make sure we dont overflow the cursor */
		if(vt100.screen[vt100.cursor.row][0].double_width && vt100.cursor.col > VT100_WIDTH/2)
		{
			vt100.cursor.col /=2;
		}
		
		nokia1100_gotoyx(vt100.cursor.row, vt100.cursor.col * NOKIA1100_WIDTH_CHAR);
		
		vt100_print_char(vt100.cursor.row, vt100.cursor.col, vt100.mode.cursor_state);
		/* } */
	}
}

void
msp430_init()
{
	/* hold watch dog timer */
	WDTCTL = WDTPW + WDTHOLD;
	
	/* If calibration constant erased */
	if (CALBC1_16MHZ == 0xFF)
	{
		/* do not load, trap CPU!! */								
		while(1);
	}
	
	/*
	 * MCLK  @ 16MHz
	 * SMCLK @ 4MHz
	 */
	
	DCOCTL = CALDCO_16MHZ;  /* Set DCO step and modulation */
	BCSCTL1 = CALBC1_16MHZ; /* Set range */
	BCSCTL2 = DIVS_2;
}
