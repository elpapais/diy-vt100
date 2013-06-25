#include <diy-vt100/setup.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/param.h>
#include <diy-vt100/setting.h>

#include <diy-vt100/screen.h>
#include <diy-vt100/hardware.h>
#include <diy-vt100/vt100/state.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/vt100/misc.h>

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
	state_noparam	(ASCII_DC2, setup_recall), /* CTRL-R pressed */
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
	state_select	('[', setup_state_arrow_select),
	
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
	setting.bits.SETUP_SHOW ^= TRUE;

	if(setting.bits.SETUP_SHOW)
	{
		/* enter setup */
		uart_loopback(ENABLE);
		state_current = (struct __state *)setup_state_type;
		
		/* switch to setupA */
		setting.bits.SETUP_TYPE = FALSE;
		setupA_load();
		setupA_refresh();
	}
	else
	{
		/* exit setup */
		
		vt100_refresh_connect_mode();
		
		state_current = (struct __state *)vt100_state_C0;
		screen_splash();
	}
}

void setup_switch(void)
{
	setup_number = 0;
	
	/* invert setting (A to B) or (B to A) */
	setting.bits.SETUP_TYPE ^= TRUE;
	
	if(setting.bits.SETUP_TYPE)
	{
		/* high show setup B */
		setupB_load();
	}
	else
	{
		/* low show setup A */
		setupA_load();
	}
}

void setup_state_worker(void)
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
			
			if(setting.bits.SETUP_TYPE)
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

void setup_brightness_increase(void)
{
	/* increase brightness */
	if(setting.brightness < SCREEN_BRIGHTNESS_MAX)
	{
		screen_brightness(++setting.brightness);
	}
}

void setup_brightness_decrease(void)
{
	/* decrease brightness */
	if(setting.brightness > SCREEN_BRIGHTNESS_MIN)
	{
		screen_brightness(--setting.brightness);
	}
}

void setup_previous_setting(void)
{
	/* select left value */
	setup_number--;
	
	/* limit to 16 only */
	setup_number &= 0x0F;
}

void setup_next_setting(void)
{
	/* select right value */
	setup_number++;
	
	/* limit to 16 only */
	setup_number &= 0x0F;
}

void setup_value_flip(void)
{
	/* flip values in setup, 5 was pressed */
	
	if(setting.bits.SETUP_TYPE)
	{
		switch(setup_number)
		{
			/* box 1 */
			case 0:
				setting.bits.DECSCLM ^= TRUE;
			break;
			
			case 1:
				setting.bits.DECARM ^= TRUE;
			break;
			
			case 2:
				setting.bits.DECSCNM ^= TRUE;
			break;
			
			case 3:
				setting.bits.CURSOR ^= TRUE;
			break;
			
			/* box 2 */
			case 4:
				setting.bits.MARGINBELL ^= TRUE;
			break;
			
			case 5:
				setting.bits.KEYCLICK ^= TRUE;
			break;
			
			case 6:
				setting.bits.DECANM ^= TRUE;
			break;
			
			case 7:
				setting.bits.AUTOX ^= TRUE;
			break;
			
			/* box 3 */
			case 8:
				setting.bits.SHIFTED ^= TRUE;
			break;
			
			case 9:
				setting.bits.DECAWM ^= TRUE;
			break;
			
			case 10:
				setting.bits.LNM ^= TRUE;
			break;
			
			case 11:
				setting.bits.DECINLM ^= TRUE;
			break;
			
			/* box 4 */
			case 12:
				setting.bits.PARITYSENSE ^= TRUE;
			break;
			
			case 13:
				setting.bits.PARITY ^= TRUE;
			break;
			
			case 14:
				setting.bits.BPC ^= TRUE;
			break;
			
			case 15:
				/* setting_flip(SETTING_POWER); */
			break;
		}
	}
}

void setup_DECCOLM(void)
{
	/* is it setup A */
	if(! setting.bits.SETUP_TYPE)
	{
		setting.bits.DECCOLM ^= TRUE;
	}
}

void setup_LOCAL(void)
{
	setting.bits.LOCAL ^= TRUE;
}

void setup_TABS_clear(void)
{
	/* is it setup A */
	if(! setting.bits.SETUP_TYPE)
	{
		setting_tabs_clear();
	}
}

void setup_TAB_flip(void)
{
	if(! setting.bits.SETUP_TYPE)
	/* is it setup A */
	{
		setting_tab_flip(setup_number);
	}
}

void setup_uart_rx(void)
{
	/* handle speeds */
	if(!(++setting.uart_rx < UART_SPEED_COUNT))
	{
		setting.uart_rx = 0;
	}
}

void setup_uart_tx(void)
{
	/* handle speeds */
	if(!(++setting.uart_tx < UART_SPEED_COUNT))
	{
		setting.uart_tx = 0;
	}
}

void setup_recall(void)
{
	setup_show_wait();
	setting_load();
	
	/* now switch to setupA */
	setting.bits.SETUP_TYPE = FALSE;
	setupA_load();
}

void setup_save(void)
{
	setup_show_wait();
	setting_store();
	
	/* now switch to setupA */
	setting.bits.SETUP_TYPE = FALSE;
	setupA_load();
}
