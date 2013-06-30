#include <diy-vt100/msp430g2553/cqueue.h>
#include <diy-vt100/msp430g2553/ic_74xx595.h>
#include <diy-vt100/msp430g2553/cqueue.h>
#include <diy-vt100/msp430g2553/port2.h>

#include <diy-vt100/common.h>
#include <diy-vt100/screen.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/param.h>
#include <diy-vt100/uart.h>

#include <diy-vt100/vt100/state.h>
#include <diy-vt100/vt100/misc.h>


void usciA0_init(void);
void flash_init(void);
void msp430_init(void);
void timer1_A3_init(void);
void ps2kbd_decode(uint8_t);
void wdt_init(void);
void port1_init(void);
void port2_init(void);

void screen_splash(void);
void screen_init(void);
void screen_refresh(void);

extern cqueue_t uart_tx;
extern cqueue_t uart_rx;
extern cqueue_t ps2kbd;

inline void __autox_feature(void);
inline void __init(void);

void
main(void)
{
	__init();
	
	__loop:
		while(ps2kbd.count)
		{
			ps2kbd_decode(cqueue_pop(&ps2kbd));
		}
		
		/* use AUTO XON */
		__autox_feature();
		
		while(uart_rx.count)
		{
			vt100_state(cqueue_pop(&uart_rx));
		}
		
		ic_74xx595_refresh();
		
		screen_refresh();
		
		_BIS_SR(LPM1_bits + GIE);
	goto __loop;
}

inline void __init()
{
	msp430_init();
	
	/* hardware dependent code */
	port1_init();
	port2_init();
	wdt_init();
	timer1_A3_init();
	flash_init();
	usciA0_init();
	vt100_init();
	screen_init();
	
	screen_brightness(parm_setting.brightness);
	screen_invert(parm_setting.bits.DECSCNM);
	
	/* show splash screen */
	screen_splash();
}

void
msp430_init(void)
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
}

inline void __autox_feature(void)
{
	/* AUTOX is enabled */
	if(parm_setting.bits.AUTOX)
	{
		/* we are half way in buffer */
		if(!(uart_rx.count < 16))
		{
			/* XOFF isnt send */
			if(! setting.bits.XOFF_SEND)
			{
				uart_send(ASCII_XOFF);
				setting.bits.XOFF_SEND = TRUE;
				setting.bits.XOFF_SCROLL = FALSE;
			}
		}
		/* is RX buffer empty */
		else if(! uart_rx.count)
		{
			/* XON is send */
			if(setting.bits.XOFF_SEND)
			{
				uart_send(ASCII_XON);
				setting.bits.XOFF_SEND = FALSE;
				setting.bits.XOFF_SCROLL = FALSE;
			}
		}
	}
}
