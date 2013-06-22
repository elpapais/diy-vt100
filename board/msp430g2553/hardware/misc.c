#include <diy-vt100/hardware/misc.h>
#include <diy-vt100/hardware/timer1_A3.h>
#include <diy-vt100/hardware/wdt.h>
#include <diy-vt100/hardware/port1.h>
#include <diy-vt100/hardware/port2.h>
#include <diy-vt100/hardware/ic_74xx595.h>
#include <diy-vt100/hardware/led.h>
#include <diy-vt100/hardware/nokia1100.h>

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
	ic_74xx595_init();
	port2_init();
	wdt_init();
	timer1_A3_init();
	nokia1100_init();
}

void hardware_reset()
{
	WDTCTL = 0;
}
