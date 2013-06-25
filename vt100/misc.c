#include <diy-vt100/vt100/misc.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/vt100/state.h>

#include <diy-vt100/param.h>
#include <diy-vt100/state-machine.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/hardware.h>
#include <diy-vt100/bell.h>
#include <diy-vt100/led.h>

void vt100_init()
{
	/* TODO: support Keyboard lock */

	param.data[0] = 2;
	vt100_ED();
	
	setting.bits.LOCAL = FALSE;
	vt100_refresh_connect_mode();
	
	state_current = (struct __state *)vt100_state_C0;
}

void vt100_refresh_connect_mode()
{
	const static uartlopbk_t map_lp_bk[2] = { DISABLE, ENABLE };
	const static led_t led_to_off[] = {LOCAL, LINE};
	const static led_t led_to_on[] = {LINE, LOCAL};

	if(uart_disconnected())
	{
		/* force local mode if disconnected */
		setting.bits.LOCAL = TRUE;
	}
	
	uart_loopback(map_lp_bk[setting.bits.LOCAL]);
	led_off(led_to_off[setting.bits.LOCAL]);
	led_on(led_to_on[setting.bits.LOCAL]);
}

bool_t __is_vt100_malfunctioning()
{
	return FALSE;
}

/* invoke self confidence test */
void 
vt100_DECTST()
{
	/* TODO: test the terminal */
}

/* keypad application mode */
void
vt100_DECKPAM()
{
	setting.bits.DECKPAM = (param.data[0]) ? TRUE : FALSE;
}

/* reset to inital state (as on power on) */
void 
vt100_RIS()
{
	/* reset MSP430 */
	hardware_reset();
}

/* cursor key mode */
void
vt100_DECCKM()
{
	setting.bits.DECCKM = TRUE;
}

/* screen in reverse vedio mode */
void vt100_DECSCNM()
{
	setting.bits.DECSCNM = (param.data[0]) ? TRUE : FALSE;
}

/* send answerback message */
void vt100_ENQ()
{
	for(uint8_t i=0; i < answerback_size; i++)
	{
		uart_send(parm_setting.answerback[i]);
	}
}

void vt100_setting_high()
{
	switch(param.data[0])
	{
		case 1:
			setting.bits.DECCKM = TRUE;
		break;
		
		case 3:
			setting.bits.DECCOLM = TRUE;
		break;
		
		case 4:
			setting.bits.DECSCLM = TRUE;
		break;
		
		case 5:
			setting.bits.DECSCNM = TRUE;
		break;
		
		case 6:
			setting.bits.DECCOM = TRUE;
		break;
		
		case 7:
			setting.bits.DECAWM = TRUE;
		break;
		
		case 8:
			setting.bits.DECARM = TRUE;
		break;
		
		case 9:
			setting.bits.DECINLM = TRUE;
		break;
		
		case 20:
			setting.bits.LNM = TRUE;
		break;
	}
}

void vt100_setting_low()
{
	switch(param.data[0])
	{
		case 1:
			setting.bits.DECCKM = FALSE;
		break;
		
		case 2:
			setting.bits.DECANM = FALSE;
		break;
		
		case 3:
			setting.bits.DECCOLM = FALSE;
		break;
		
		case 4:
			setting.bits.DECSCLM = FALSE;
		break;
		
		case 5:
			setting.bits.DECSCNM = FALSE;
		break;
		
		case 6:
			setting.bits.DECCOM = FALSE;
		break;
		
		case 7:
			setting.bits.DECAWM = FALSE;
		break;
		
		case 8:
			setting.bits.DECARM = FALSE;
		break;
		
		case 9:
			setting.bits.DECINLM = FALSE;
		break;
		
		case 20:
			setting.bits.LNM = FALSE;
		break;
	}
}

void vt100_sequence_terminate()
{
	/* reset to C0 state (this work is already preformed by worker function) */
	//state_current = (struct __state)vt100_state_C0;

	/* TODO: print error char */
}

/* load led's */
void 
vt100_DECLL()
{
	for(register uint8_t i=0; i < param.count; i++)
	{
		switch(param.data[i])
		{
			case 0:
				led_off(PROG1);
				led_off(PROG2);
				led_off(PROG3);
				led_off(PROG4);
			break;
			
			case 1:
				led_on(PROG1);
			break;
			
			case 2:
				led_on(PROG2);
			break;
			
			case 3:
				led_on(PROG3);
			break;
			
			case 4:
				led_on(PROG4);
			break;
		}
	}
}
