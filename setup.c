#include <diy-vt100/setup.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/param.h>
#include <diy-vt100/setting.h>

#include <diy-vt100/screen.h>
#include <diy-vt100/hardware.h>
#include <diy-vt100/vt100/state.h>
#include <diy-vt100/vt100/cursor.h>

extern const struct __state setup_state_type[];
extern const struct __state setup_state_arrow[];
extern const struct __state setup_state_arrow_select[];

uint8_t setup_number;

const struct __state
setup_state_type[] = 
{
	state_worker	(setup_state_worker),
	
	state_select	(ASCII_ESCAPE, setup_state_arrow),
	state_noparam	(ASCII_DC3, setup_save), /* CTRL-S pressed */
	state_noparam	(ASCII_DC2, setting_load), /* CTRL-R pressed */
	state_noparam	('0', hardware_reset),
	state_noparam	('2', setup_TAB_flip),
	state_noparam	('3', setup_TABS_clear),
	state_noparam	('4', setup_LOCAL),
	state_noparam	('5', setup_switch),
	state_noparam	('6', setup_value_flip),
	state_noparam	('7', setup_uart_tx), /* transmit speed */
	state_noparam	('8', setup_uart_rx), /* receive speed */
	state_noparam	('9', setup_DECCOLM),
	state_noparam	(ASCII_LF, setup_next_setting),
	state_noparam	(ASCII_SPACE, setup_next_setting),
	state_noparam	(ASCII_TAB, setup_next_setting),
	state_end()
};

const struct __state
setup_state_arrow[] = 
{
	state_worker	(setup_state_worker),
	
	state_select	('O', setup_state_arrow_select),
	state_select	('?', setup_state_arrow_select),
	
	state_noparam	('A', setup_brightness_increase),
	state_noparam	('B', setup_brightness_decrease),
	state_noparam	('C', setup_next_setting),
	state_noparam	('D', setup_previous_setting),
	state_end		()
};

const struct __state
setup_state_arrow_select[] =
{
	state_worker	(setup_state_worker),
	
	state_noparam	('A', setup_brightness_increase),
	state_noparam	('B', setup_brightness_decrease),
	state_noparam	('C', setup_next_setting),
	state_noparam	('D', setup_previous_setting),
};

void setup()
{
	setting_flip(SETTING__SETUP_SHOW);

	if(setting_ishigh(SETTING__SETUP_SHOW))
	{
		/* enter setup */
		uart_loopback_enable();
		state_current = (struct __state *)setup_state_type;
		
		/* simulate STATE B */
		setting_high(SETTING__SETUP_TYPE);
		setup_switch();
	}
	else
	{
		/* exit setup */
		
		if(setting_islow(SETTING__LOCAL))
		{
			uart_loopback_disable();
		}
		
		state_current = (struct __state *)vt100_state_C0;
		screen_splash();
	}
	
	
}

void setup_switch()
{
	setup_number = 0;
	
	/* invert setting (A to B) or (B to A) */
	setting_flip(SETTING__SETUP_TYPE);
	
	if(setting_ishigh(SETTING__SETUP_TYPE))
	{
		/* high show setup B */
		setupB_load();
		setupB_refresh();
	}
	else
	{
		/* low show setup A */
		setupA_load();
		setupA_refresh();
	}
}

void setup_state_worker()
{	
	switch((int)state_iterate->cb)
	{
		case 0:
		case 1:
			/* ignore (missing or instructed to ignored) */
		return;
		
		case 2:
			state_current = (struct __state *)state_iterate->arg.state;
		break;
		
		default:
			/* restore state */
			state_current = (struct __state *)setup_state_type;
			
			state_iterate->cb();
			
			if(setting_ishigh(SETTING__SETUP_TYPE))
			{
				/* high show setup B */
				setupB_refresh();
			}
			else
			{
				/* low show setup A */
				setupA_refresh();
			}
		break;
	}
}

void setup_brightness_increase()
{
	/* increase brightness */
	if(setting.brightness < SCREEN_BRIGHTNESS_MAX)
	{
		screen_brightness(++setting.brightness);
	}
}

void setup_brightness_decrease()
{
	/* decrease brightness */
	if(setting.brightness > SCREEN_BRIGHTNESS_MIN)
	{
		screen_brightness(--setting.brightness);
	}
}

void setup_previous_setting()
{
	/* select left value */
	setup_number--;
	
	/* limit to 16 only */
	setup_number &= 0x0F;
}

void setup_next_setting()
{
	/* select right value */
	setup_number++;
	
	/* limit to 16 only */
	setup_number &= 0x0F;
}

void setup_value_flip()
{
	/* flip values in setup, 5 was pressed */
	
	if(setting_ishigh(SETTING__SETUP_TYPE))
	{
		switch(setup_number)
		{
			/* box 1 */
			case 0:
				setting_flip(SETTING_CURSOR);
			break;
			
			case 1:
				setting_flip(SETTING_DECSCNM);
			break;
			
			case 2:
				setting_flip(SETTING_DECARM);
			break;
			
			case 3:
				setting_flip(SETTING_DECSCLM);
			break;
			
			/* box 2 */
			case 4:
				setting_flip(SETTING_MARGINBELL);
			break;
			
			case 5:
				setting_flip(SETTING_KEYCLICK);
			break;
			
			case 6:
				setting_flip(SETTING_DECANM);
			break;
			
			case 7:
				setting_flip(SETTING_AUTOX);
			break;
			
			/* box 3 */
			case 8:
				setting_flip(SETTING_SHIFTED);
			break;
			
			case 9:
				setting_flip(SETTING_DECAWM);
			break;
			
			case 10:
				setting_flip(SETTING_LNM);
			break;
			
			case 11:
				setting_flip(SETTING_DECINLM);
			break;
			
			/* box 4 */
			case 12:
				setting_flip(SETTING_PARITYSENSE);
			break;
			
			case 13:
				setting_flip(SETTING_PARITY);
			break;
			
			case 14:
				setting_flip(SETTING_BPC);
			break;
			
			case 15:
				/* setting_flip(SETTING_POWER); */
			break;
		}
	}
}

void setup_DECCOLM()
{
	/* is it setup A */
	if(setting_islow(SETTING__SETUP_TYPE))
	{
		setting_flip(SETTING_DECCOLM);
	}
}

void setup_LOCAL()
{
	setting_flip(SETTING__LOCAL);
}

void setup_TABS_clear()
{
	/* is it setup A */
	if(setting_islow(SETTING__SETUP_TYPE))
	{
		setting_tabs_clear();
	}
}

void setup_TAB_flip()
{
	/* is it setup A */
	if(setting_islow(SETTING__SETUP_TYPE))
	{
		setting_tab_flip(setup_number);
	}
}

void setup_uart_rx()
{
	/* handle speeds */
	if(!(++setting.uart_rx < UART_SPEED_COUNT))
	{
		setting.uart_rx = 0;
	}
}

void setup_uart_tx()
{
	/* handle speeds */
	if(!(++setting.uart_tx < UART_SPEED_COUNT))
	{
		setting.uart_tx = 0;
	}
}
