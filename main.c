#include <msp430.h>
#include <common.h>
#include <nokia1100.h>
#include <splash.h>
#include <vt100/vt100.h>
#include <interrupt/timerA.h>
#include <interrupt/usci0.h>
#include <interrupt/port2.h>

void msp430_init();

int
main()
{
	msp430_init();
	nokia1100_init();
	vt100_init();
	
	splash();
	
	usci0_init();
	timerA_init();
	port2_init();
	
	while(TRUE)
	{
		_BIS_SR(LPM0_bits + GIE);
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
	 * SMCLK @ 2MHz
	 */
	 
	DCOCTL = CALDCO_16MHZ;  /* Set DCO step and modulation */
	BCSCTL1 = CALBC1_16MHZ; /* Set range */
	BCSCTL2 = DIVS_2;
}
