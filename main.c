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
		while(uart_cqueue_rx.count)
		{
			vt100_param.pass = cqueue_pop(&uart_cqueue_rx);
			control();
		}
		
		vt100_screen_refresh();
		/* } */
		
		vt100_cursor_draw();
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
