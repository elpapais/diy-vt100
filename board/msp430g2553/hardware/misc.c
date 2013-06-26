#include <diy-vt100/hardware.h>
#include <diy-vt100/hardware/wdt.h>
#include <diy-vt100/hardware/port1.h>
#include <diy-vt100/hardware/port2.h>
#include <diy-vt100/hardware/ic_74xx595.h>
#include <diy-vt100/hardware/keyboard/ps2.h>
#include <diy-vt100/hardware/uart.h>
#include <diy-vt100/hardware/cqueue.h>
#include <diy-vt100/param.h>
#include <diy-vt100/screen.h>
#include <diy-vt100/vt100/state.h>

void timer1_A3_init(void);

/*
 * usuage of setting bits 
 * setting.bits.HW_PRIV0 : cursor blink state
 * setting.bits.HW_PRIV1 : keyboard modifier
 * setting.bits.HW_PRIV2 : keyboard break
 * setting.bits.HW_PRIV3 : not used(maybe keybpard PARITY)
 * 
 * their maybe preprocessor directive to 
 * replace decscriptive names with their crossponding HW_PRIV#
 */

void
hardware_init(void)
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

void hardware_reset(void)
{
	WDTCTL = 0;
}

void hardware_loop(void)
{
__loop:
	while(ps2kbd.count)
	{
		ps2kbd_decode(cqueue_pop(&ps2kbd));
	}
	
	while(uart_rx.count)
	{
		vt100_state(cqueue_pop(&uart_rx));
	}
	
	screen_refresh();
	
	ic_74xx595_refresh();
	_BIS_SR(LPM1_bits + GIE);
goto __loop;
}
