#include <msp430.h>
#include <nokia1100.h>
#include <splash.h>
#include <vt100/vt100.h>
#include <uart.h>

void msp430_init();

int
main()
{
	msp430_init();
	nokia1100_init();
	vt100_init();
	
	splash();
	
	uart_init();
	vt100_cursor();
	_BIS_SR(LPM0_bits + GIE);
	
	while(1);
}

void
msp430_init()
{
	/* hold watch dog timer */
	WDTCTL = WDTPW + WDTHOLD;
	
	/* If calibration constant erased */
	if (CALBC1_1MHZ==0xFF)
	{
		/* do not load, trap CPU!! */								
		while(1);
	}
	
	/* NOTE:
	 * if frequency of DCO is (8MHz) and mclk is feeded /8, uart dont work
	 * if frequency of DCO is 1Mhz and mclk is feeded /1, uart works
	 * 
	 * also, for heigher other setting it also dont work :(
	 * might be due to unstable internal clock
	 */
	
	/*
	 * MCLK  @ 1MHz
	 * ACLK  @ 125KHz
	 * SMCLK @ 1MHz
	 */
	 
	DCOCTL = CALDCO_1MHZ;  /* Set DCO step and modulation */
	BCSCTL1 = CALBC1_1MHZ + DIVA_3; /* Set range */
	BCSCTL2 = DIVS_0;
}
