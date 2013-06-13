#include <vt100/misc.h>
#include <vt100/cursor.h>
#include <param.h>
#include <vt100/buffer.h>
#include <vt100/state.h>
#include <vt100/bell.h>
#include <hardware/led.h>
#include <state-machine.h>
#include <setting.h>
#include <hardware/misc.h>

void vt100_init()
{
	led_on(LED_ONLINE);
	led_refresh();
	
	/* TODO: check power online/offline mode & keyboard connected */
	/* TODO: support offline mode */
	/* TODO: support Keyboard lock */

	param.data[0] = 2;
	vt100_ED();
	
	state_current = (struct __state *)vt100_state_C0;
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
	if(param.data[0])
	{
		setting_high(SETTING_DECKPAM);
	}
	else
	{
		setting_low(SETTING_DECKPAM);
	}
	
}

/* reset to inital state (as on power on) */
void 
vt100_RIS()
{
	/* reset MSP430 */
	hw_reset();
}

/* cursor key mode */
void
vt100_DECCKM()
{
	setting_high(SETTING_DECCKM);
}

/* screen in reverse vedio mode */
void vt100_DECSCNM()
{
	if(param.data[0])
	{
		setting_high(SETTING_DECSCNM);
		nokia1100_invertpixel_on();
	}
	else
	{
		setting_low(SETTING_DECSCNM);
		nokia1100_invertpixel_off();
	}
	
	
}

/* send answerback message */
void vt100_ENQ()
{
	uint8_t i = 0;

	for(i=0; i < SETTING_ANSWERBACK_SIZE; i++)
	{
		uart_send(setting.answerback[i]);
	}
}

void vt100_setting_high()
{
	switch(param.data[0])
	{
		case 1:
			setting_high(SETTING_DECCKM);
		break;
		
		case 3:
			setting_high(SETTING_DECCOLM);
		break;
		
		case 4:
			setting_high(SETTING_DECSCLM);
		break;
		
		case 5:
			setting_high(SETTING_DECSCNM);
		break;
		
		case 6:
			setting_high(SETTING_DECOM);
		break;
		
		case 7:
			setting_high(SETTING_DECAWM);
		break;
		
		case 8:
			setting_high(SETTING_DECARM);
		break;
		
		case 9:
			setting_high(SETTING_DECINLM);
		break;
		
		case 20:
			setting_high(SETTING_LNM);
		break;
	}
}

void vt100_setting_low()
{
	switch(param.data[0])
	{
		case 1:
			setting_low(SETTING_DECCKM);
		break;
		
		case 2:
			setting_low(SETTING_DECANM);
		break;
		
		case 3:
			setting_low(SETTING_DECCOLM);
		break;
		
		case 4:
			setting_low(SETTING_DECSCLM);
		break;
		
		case 5:
			setting_low(SETTING_DECSCNM);
		break;
		
		case 6:
			setting_low(SETTING_DECOM);
		break;
		
		case 7:
			setting_low(SETTING_DECAWM);
		break;
		
		case 8:
			setting_low(SETTING_DECARM);
		break;
		
		case 9:
			setting_low(SETTING_DECINLM);
		break;
		
		case 20:
			setting_low(SETTING_LNM);
		break;
	}
}
