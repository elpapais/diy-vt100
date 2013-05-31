#include <hardware/port1.h>
#include <setup.h>

bool_t button;

void port1_init()
{
	P1DIR |= SETUP_BUTTON; 
	
	P1IE |=  SETUP_BUTTON;
	P1IES |= SETUP_BUTTON;
	P1REN |= SETUP_BUTTON;
	P1IFG &= ~SETUP_BUTTON;
	
	/* interrupt goes to port1_interrupt() */
}

void port1_interrupt()
{
	if(button)
	{
		setup_enter();
	}
	else
	{
		setup_exit();
	}
	
	button ^= TRUE;
	
	P1IFG &= ~SETUP_BUTTON;
}
