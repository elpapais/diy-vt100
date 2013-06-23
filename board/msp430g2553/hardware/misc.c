#include <diy-vt100/hardware.h>
#include <diy-vt100/hardware/wdt.h>
#include <diy-vt100/hardware/port1.h>
#include <diy-vt100/hardware/port2.h>
#include <diy-vt100/hardware/ic_74xx595.h>

void timer1_A3_init();

void
hardware_init()
{
	/* hold watch dog timer */
	WDTCTL = WDTPW + WDTHOLD;
	
	/* If calibration constant erased */
	if(CALBC1_16MHZ == 0xFF)
	{
		/* go in low power mode!! */
		__do_nothing: goto __do_nothing;
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
	
	/* hardware dependent code */
	port1_init();
	port2_init();
	wdt_init();
	timer1_A3_init();
}

void hardware_reset()
{
	WDTCTL = 0;
}

void refresh_finished()
{
	ic_74xx595_refresh();
	_BIS_SR(LPM1_bits + GIE);
}
