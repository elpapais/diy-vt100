#include <msp430.h>
#include <common.h>
#include <splash.h>
#include <vt100/vt100.h>
#include <hardware/timerA.h>
#include <hardware/port2.h>
#include <hardware/usciA.h>

void msp430_init();

void
main()
{
	msp430_init();
	port1_init();
	vt100_init();
	
	splash();
	
	usciA_init();
	timerA_init();
	port2_init();

	loop:
		vt100_cursor_draw();
		
		_BIS_SR(LPM1_bits + GIE);
		
		/* screen refresh { */
		while(uart_rx.count)
		{
			vt100_param.pass = cqueue_pop(&uart_rx);
			control();
		}
		
		vt100_screen_refresh();
		/* } */
	goto loop;
}

void
msp430_init()
{
	/* hold watch dog timer */
	WDTCTL = WDTPW + WDTHOLD;
	
	/* If calibration constant erased */
	if(CALBC1_16MHZ == 0xFF)
	{
		/* go in low power mode!! */							
		_BIS_SR(LPM4_bits);
	}
	
	/*
	 * MCLK  @ 16MHz
	 * SMCLK @ 4MHz
	 */
	
	/* Set DCO step and modulation */
	DCOCTL = CALDCO_16MHZ;
	
	/* Set range */ 
	BCSCTL1 = CALBC1_16MHZ;
	BCSCTL2 = DIVS_2;
}
