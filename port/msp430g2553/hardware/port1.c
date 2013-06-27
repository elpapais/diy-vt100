#include <diy-vt100/hardware/port1.h>
#include <diy-vt100/setup.h>

void port1_interrupt(void)__attribute__((interrupt(PORT1_VECTOR)));

void port1_init(void)
{
	P1DIR |= IC_74XX595_DATA | IC_74XX595_STCP | IC_74XX595_SHCP;
	
	P1OUT &= ~(IC_74XX595_DATA | IC_74XX595_STCP | IC_74XX595_SHCP);
	
	P1DIR |= SETUP_BUTTON; 
	
	P1IE |=  SETUP_BUTTON;
	P1IES |= SETUP_BUTTON;
	P1REN |= SETUP_BUTTON;
	P1IFG &= ~SETUP_BUTTON;
	
	/* interrupt goes to port1_interrupt() */
}

void port1_interrupt(void)
{
	setup();
	P1IFG &= ~SETUP_BUTTON;
}
