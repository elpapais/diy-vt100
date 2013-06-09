#include <msp430.h>
#include <common.h>

#include <hardware/timer1_A3.h>
#include <hardware/wdt.h>
#include <hardware/port1.h>
#include <hardware/port2.h>
#include <hardware/ic_74xx595.h>
#include <hardware/buzzer.h>
#include <hardware/led.h>
#include <hardware/usciA0.h>
#include <hardware/keyboard-ps2.h>
#include <hardware/nokia1100.h>

#include <splash.h>
#include <param.h>
#include <uart.h>
#include <state-machine.h>
#include <vt100/misc.h>
#include <vt100/screen.h>
#include <setting.h>

void msp430_init();

void
main()
{
	/* hardware dependent code */
	msp430_init();
	flash_init();
	port1_init();
	ic_74xx595_init();
	port2_init();
	usciA0_init();
	//timer0_A3_init();
	wdt_init();
	timer1_A3_init();
	
	/* no hardware dependent code */
	setting_init();
	nokia1100_init();
	vt100_init();
	uart_init();
	
	/* show splash screen */
	splash();
	
	__loop:
		while(keyboard_ps2.data_queue.count)
		{
			keyboard_ps2.param = cqueue_pop(&keyboard_ps2.data_queue);
			keyboard_ps2_data_decode();
		}
		
		while(uart_rx_count())
		{
			param.pass = uart_rx_pop();
			state_do();
		}
		
		vt100_screen_refresh();
		_BIS_SR(LPM1_bits + GIE);
	goto __loop;
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
