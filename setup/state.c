#include <setup.h>
#include <param.h>
#include <nokia1100.h>
#include <vt100/buffer.h>
#include <hardware/timer1_A3.h>
#include <setting.h>

uint8_t setup_type_current;
uint8_t setup_setting_number;

const struct __state
setup_state_type[] = 
{
	state_noparam	(0, setup_state_worker),
	
	state_select	(ASCII_ESCAPE, setup_state_arrow),
	state_noparam	('5', setup_switch),
	state_noparam	('6', setup_value_flip),
	state_end()
};

const struct __state
setup_state_arrow[] = 
{
	state_noparam	(0, setup_state_worker),
	
	state_select	('O', setup_state_arrow_select),
	state_select	('?', setup_state_arrow_select),
	
	state_noparam	('A', setup_arrow_up),
	state_noparam	('B', setup_arrow_down),
	state_noparam	('C', setup_arrow_right),
	state_noparam	('D', setup_arrow_left),
	state_end		()
};

const struct __state
setup_state_arrow_select[] =
{
	state_noparam	(0, setup_state_worker),
	
	state_noparam	('A', setup_arrow_up),
	state_noparam	('B', setup_arrow_down),
	state_noparam	('C', setup_arrow_right),
	state_noparam	('D', setup_arrow_left),
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
		break;
	}
}

void setup_arrow_up()
{
	/* increase brightness */
	if(setting_brightness < TIMER1_A3_PWM_MAX)
	{
		timer1_A3_pwm(++setting_brightness);
	}
}

void setup_arrow_down()
{
	/* decrease brightness */
	if(setting_brightness > TIMER1_A3_PWM_MIN)
	{
		timer1_A3_pwm(--setting_brightness);
	}
}

void setup_arrow_left()
{
	/* select left value */
	setup_setting_number--;
	
	(setup_type_current == 'B') ? setup_B_refresh() : setup_A_refresh();
}

void setup_arrow_right()
{
	/* select right value */
	setup_setting_number++;
	
	(setup_type_current == 'B') ? setup_B_refresh() : setup_A_refresh();
}

void setup_value_flip()
{
	/* flip values in setup, 5 was pressed */
	
	if(setup_type_current == 'B')
	{
		setup_setting_number &= 0x0F;
		
		switch(setup_setting_number)
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
		
		setup_B_refresh();
	}
}

void setup_switch()
{
	setup_setting_number = 0;
	
	if(setup_type_current == 'B')
	{
		setup_type_current = 'A';
		vt100_buffer_copy(buffer_setupA);
		setup_A_refresh();
	}
	else
	{
		setup_type_current = 'B';
		vt100_buffer_copy(buffer_setupB);
		setup_B_refresh();
	}
}

void setup_B_refresh()
{
	/* limit to 16 only */
	setup_setting_number &= 0x0F;
	
	setup_print_value(6, 2, setting_read(SETTING_CURSOR), 0 );
	setup_print_value(6, 3, setting_read(SETTING_DECSCNM), 1);
	setup_print_value(6, 4, setting_read(SETTING_DECARM), 2);
	setup_print_value(6, 5, setting_read(SETTING_DECSCLM), 3);
	
	setup_print_value(6, 9, setting_read(SETTING_MARGINBELL), 4);
	setup_print_value(6, 10, setting_read(SETTING_KEYCLICK), 5);
	setup_print_value(6, 11, setting_read(SETTING_DECANM), 6);
	setup_print_value(6, 12, setting_read(SETTING_AUTOX), 7);
	
	setup_print_value(7, 2, setting_read(SETTING_SHIFTED), 8);
	setup_print_value(7, 3, setting_read(SETTING_DECAWM), 9);
	setup_print_value(7, 4, setting_read(SETTING_LNM), 10);
	setup_print_value(7, 5, setting_read(SETTING_DECINLM), 11);
	
	setup_print_value(7, 9, setting_read(SETTING_PARITYSENSE), 12);
	setup_print_value(7, 10, setting_read(SETTING_PARITY), 13);
	setup_print_value(7, 11, setting_read(SETTING_BPC), 14);
	setup_print_value(7, 12, 0 /* setting_read(SETTING_POWER) */, 15);
}

void setup_A_refresh()
{
	
}

void setup_print_value(row_t row, col_t col, bool_t val, uint8_t value_no)
{
	vt100_buffer[row][0].prop |= VT100_CHAR_PROP_TOUCH;
	
	if(value_no == setup_setting_number)
	{
		vt100_buffer[row][col].prop &= ~VT100_CHAR_PROP_INVERSE;
	}
	else
	{
		vt100_buffer[row][col].prop |= VT100_CHAR_PROP_INVERSE;
	}
	
	if(val)
	{
		vt100_buffer[row][col].data = '1';
	}
	else
	{
		vt100_buffer[row][col].data = '0';
	}
}
