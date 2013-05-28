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
	uint8_t data = 0;
	msp430_init();
	port1_init();
	vt100_init();
	usciA_init();
	timerA_init();
	port2_init();
	
	splash();

	vt100_setting.mode |= VT100_SETTING_MODE_CURSOR_DESIGN;
	
	__loop:
		while(keyboard_ps2.data_queue.count)
		{
			keyboard_ps2.param = cqueue_pop(&keyboard_ps2.data_queue);
			keyboard_ps2_data_decode();
		}
		
		while(uart_rx.count)
		{
			vt100_param.pass = cqueue_pop(&uart_rx);
			control();
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
	 * MCLK  @ 8MHz
	 * SMCLK @ 1MHz
	 */
	
	/* Set DCO step and modulation */
	DCOCTL = CALDCO_16MHZ;
	
	/* Set range */ 
	BCSCTL1 = CALBC1_16MHZ;
	BCSCTL2 = DIVS_2;
}
