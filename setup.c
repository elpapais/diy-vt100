#include <diy-vt100/setup.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/screen.h>
#include <diy-vt100/vt100/misc.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/hardware.h>

uint8_t setup_number;

void setup()
{
	setting.bits.SETUP_SHOW ^= TRUE;

	if(setting.bits.SETUP_SHOW)
	{
		/* switch to setupA */
		setup_number = 0;
		setting.bits.SETUP_TYPE = FALSE;
		setupA_load();
		setupA_refresh();
	}
	else
	{
		/* exit setup */
		vt100_refresh_connect_mode();
		screen_full_clear();
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
		setupB_refresh();
	}
	else
	{
		/* low show setup A */
		setupA_load();
		setupA_refresh();
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

	(setting.bits.SETUP_TYPE) ? setupB_refresh() : setupA_refresh();
}

void setup_next_setting(void)
{
	/* select right value */
	setup_number++;

	if(setting.bits.SETUP_TYPE)
	{
		setup_number &= 0x0F;
		
		setupB_refresh();
	}
	else
	{
		if(!(setup_number < SCREEN_COL))
		{
			setup_number = 0;
		}

		setupA_refresh();
	}
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

		setupB_refresh();
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
		setupA_refresh();
	}
}

void setup_TAB_flip(void)
{
	if(! setting.bits.SETUP_TYPE)
	/* is it setup A */
	{
		setting_tab_flip(setup_number);
		setupA_refresh();
	}
}

void setup_uart_rx(void)
{
	/* handle speeds */
	if(!(++setting.uart_rx < UART_SPEED_COUNT))
	{
		setting.uart_rx = 0;
	}

	/* in setup B */
	if(setting.bits.SETUP_TYPE)
	{
		setupB_refresh();
	}
}

void setup_uart_tx(void)
{
	/* handle speeds */
	if(!(++setting.uart_tx < UART_SPEED_COUNT))
	{
		setting.uart_tx = 0;
	}

	/* in setupB */
	if(setting.bits.SETUP_TYPE)
	{
		setupB_refresh();
	}
}

void setup_recall(void)
{
	setup_show_wait();
	setting_load();

	/* now switch to setupA */
	setting.bits.SETUP_TYPE = FALSE;
	setup_number = 0;

	setupA_load();
	setupA_refresh();
}

void setup_save(void)
{
	setup_show_wait();
	setting_store();

	/* now switch to setupA */
	setting.bits.SETUP_TYPE = FALSE;
	setup_number = 0;

	setupA_load();
	setupA_refresh();
}

void setup_reset(void)
{
	hardware_reset();
}
