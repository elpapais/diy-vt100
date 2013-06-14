#include <diy-vt100/setup.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/param.h>
#include <diy-vt100/setting.h>

#include <diy-vt100/screen.h>
#include <diy-vt100/hardware/misc.h>

#include <diy-vt100/vt100/state.h>
#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/vt100/buffer.h>



const struct __vt100_char setup_buffer_A[VT100_HEIGHT][VT100_WIDTH] =  
{
	{{'S', ROW_DOUBLE_WIDTH|ROW_DOUBLE_HEIGHT_TOP|ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'A'}},
	{{'S', ROW_DOUBLE_WIDTH|ROW_DOUBLE_HEIGHT_BOT|ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'A'}},
	{{'T', DATA_UNDERLINE|ROW_TOUCH}, {'O', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'E', DATA_UNDERLINE}, {'X', DATA_UNDERLINE}, {'I', DATA_UNDERLINE}, {'T', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'P', DATA_UNDERLINE}, {'R', DATA_UNDERLINE}, {'E', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {'2', DATA_UNDERLINE}},
	{{0, ROW_TOUCH}},
	{{0, ROW_TOUCH}},
	{{0, ROW_TOUCH}},
	{{'*', ROW_TOUCH}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}},
	{{'1', ROW_TOUCH}, {'2'}, {'3'}, {'4'}, {'5'}, {'6'}, {'7'}, {'8'}, {'9'}, {'0'}, {'1', DATA_INVERSE}, {'2', DATA_INVERSE}, {'3', DATA_INVERSE}, {'4', DATA_INVERSE}, {'5', DATA_INVERSE}, {'6', DATA_INVERSE}}
};

const struct __vt100_char setup_buffer_B[VT100_HEIGHT][VT100_WIDTH] =  
{
	{{'S', ROW_DOUBLE_WIDTH|ROW_DOUBLE_HEIGHT_TOP|ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'B'}},
	{{'S', ROW_DOUBLE_WIDTH|ROW_DOUBLE_HEIGHT_BOT|ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'B'}},
	{{'T', DATA_UNDERLINE|ROW_TOUCH}, {'O', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'E', DATA_UNDERLINE}, {'X', DATA_UNDERLINE}, {'I', DATA_UNDERLINE}, {'T', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'P', DATA_UNDERLINE}, {'R', DATA_UNDERLINE}, {'E', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {' ', DATA_UNDERLINE}, {'S', DATA_UNDERLINE}, {'2', DATA_UNDERLINE}},
	{{0, ROW_TOUCH}},
	{{'T', ROW_TOUCH}, {' '}, {'S'}, {'P'}, {'E'}, {'E'}, {'D'}, {' '}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'} },
	{{'R', ROW_TOUCH}, {' '}, {'S'}, {'P'}, {'E'}, {'E'}, {'D'}, {' '}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'} },
	{{'1', ROW_TOUCH}, {' '}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {' '}, {'2'}, {' '}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE} },
	{{'3', ROW_TOUCH}, {' '}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {' '}, {'4'}, {' '}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE}, {'0', DATA_INVERSE} },
};

void setup()
{
	setting_flip(SETTING__SETUP_SHOW);

	if(setting_ishigh(SETTING__SETUP_SHOW))
	{
		/* enter setup */
		uart_hardware_disable();
		uart_loopback_enable();
		state_current = (struct __state *)setup_state_type;
		
		/* simulate STATE B */
		setting_high(SETTING__SETUP_TYPE);
		setup_switch();
	}
	else
	{
		/* exit setup */
		uart_hardware_enable();
		uart_loopback_disable();
		
		state_current = (struct __state *)vt100_state_C0;
		splash();
	}
}

uint8_t setup_number;

const struct __state
setup_state_type[] = 
{
	state_noparam	(0, setup_state_worker),
	
	state_select	(ASCII_ESCAPE, setup_state_arrow),
	state_noparam	(ASCII_DC3, setup_save), /* CTRL-S pressed */
	state_noparam	(ASCII_DC2, setup_reload), /* CTRL-R pressed */
	state_noparam	('0', setup_reset),
	state_noparam	('2', setup_TAB_flip),
	state_noparam	('3', setup_TABS_clear),
	state_noparam	('4', setup_LOCAL),
	state_noparam	('5', setup_switch),
	state_noparam	('6', setup_value_flip),
	state_noparam	('7', setup_speed), /* transmit speed */
	state_noparam	('8', setup_speed), /* receive speed */
	state_noparam	('9', setup_DECCOLM),
	state_noparam	(ASCII_LF, setup_next_setting),
	state_noparam	(ASCII_SPACE, setup_next_setting),
	state_noparam	(ASCII_TAB, setup_next_setting),
	state_end()
};

const struct __state
setup_state_arrow[] = 
{
	state_noparam	(0, setup_state_worker),
	
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
	state_noparam	(0, setup_state_worker),
	
	state_noparam	('A', setup_brightness_increase),
	state_noparam	('B', setup_brightness_decrease),
	state_noparam	('C', setup_next_setting),
	state_noparam	('D', setup_previous_setting),
};

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
				setup_B_refresh();
			}
			else
			{
				/* low show setup A */
				setup_A_refresh();
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
	if(setting.brightness > SCREEN_BRIGHTNESS_MAX)
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

void setup_switch()
{
	setup_number = 0;
	
	/* invert setting (A to B) or (B to A) */
	setting_flip(SETTING__SETUP_TYPE);
	
	if(setting_ishigh(SETTING__SETUP_TYPE))
	{
		/* high show setup B */
		vt100_buffer_copy(setup_buffer_B);
		setup_B_refresh();
	}
	else
	{
		/* low show setup A */
		vt100_buffer_copy(setup_buffer_A);
		setup_A_refresh();
	}
}

void setup_B_refresh()
{
	row_t i;
	col_t j;
	uint8_t value_no = 0;
	
	
	bool_t readed_values[16] =
	{
		setting_ishigh(SETTING_CURSOR), setting_ishigh(SETTING_DECSCNM), setting_ishigh(SETTING_DECARM), setting_ishigh(SETTING_DECSCLM),
		setting_ishigh(SETTING_MARGINBELL), setting_ishigh(SETTING_KEYCLICK), setting_ishigh(SETTING_DECANM), setting_ishigh(SETTING_AUTOX),
		setting_ishigh(SETTING_SHIFTED), setting_ishigh(SETTING_DECAWM), setting_ishigh(SETTING_LNM), setting_ishigh(SETTING_DECINLM),
		setting_ishigh(SETTING_PARITYSENSE), setting_ishigh(SETTING_PARITY), setting_ishigh(SETTING_BPC), /*setting_ishigh(SETTING_POWER) */ 0
	};
	
	for(i = 6; i < 8; i++)
	{
		for(j=2; j < 13; j++)
		{
			if(j > 5 && j < 9)
			{
				continue;
			}
			
			vt100_buffer[i][j].data = readed_values[value_no] ? '1' : '0';
			
			if(value_no++ == setup_number)
			{
				vt100_cursor.row = i;
				vt100_cursor.col = j;
			}
		}
		
		vt100_buffer_row_touch(i);
	}
	
	const struct __vt100_char *speed_str = uart_speed_get(setting.speed);
	
	vt100_buffer_row_touch(4);
	vt100_buffer_row_touch(5);
	
	for(j=0; j < UART_SPEED_STRING_LENGTH; j++)
	{
		vt100_buffer[4][j + 8] = vt100_buffer[5][j + 8] = speed_str[j];
	}
}

void setup_A_refresh()
{
	col_t j;
	vt100_cursor.row = 6;
	vt100_cursor.col = setup_number;
	
	for(j=0; j < 16; j++)
	{
		vt100_buffer[6][j].data = setting_tab_ishigh(j) ? 'T' : ' ';
	}		
}

void setup_save()
{
	col_t j = 0;
	const struct __vt100_char saving_message[VT100_WIDTH] = {{'S', ROW_TOUCH}, {'a'}, {'v'}, {'e'}, {'d'}, {'.'}};

	/* start saving */
	setting_save();

	for(j = 0; j < VT100_WIDTH; j++)
	{
		vt100_buffer[3][j] = saving_message[j];
	}
}

void setup_reload()
{
	setting_load();
}

void setup_reset()
{
	/* restart */
	hardware_reset();
}

void setup_DECCOLM()
{
	/* is it setup A */
	if(setting_low(SETTING__SETUP_TYPE))
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
		setting_tab_clear();
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

void setup_speed()
{
	/* handle speeds */
	if(!(++setting.speed < UART_SPEED_COUNT))
	{
		setting.speed = 0;
	}
}
