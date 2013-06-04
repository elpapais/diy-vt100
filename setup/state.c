#include <setup.h>
#include <param.h>
#include <nokia1100.h>
#include <vt100/buffer.h>
#include <hardware/timer1_A3.h>

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
	if(setup_setting.brightness < TIMER1_A3_PWM_MAX)
	{
		timer1_A3_pwm(++setup_setting.brightness);
	}
}

void setup_arrow_down()
{
	/* decrease brightness */
	if(setup_setting.brightness > TIMER1_A3_PWM_MIN)
	{
		timer1_A3_pwm(--setup_setting.brightness);
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
		setup_setting.B |= (1 << setup_setting_number);
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
	
	setup_new_value(6, 2, !!(setup_setting.B & SETUP_B_CURSOR), 0 );
	setup_new_value(6, 3, !!(setup_setting.B & SETUP_B_SCREEN), 1);
	setup_new_value(6, 4, !!(setup_setting.B & SETUP_B_AUTOREPEAT), 2);
	setup_new_value(6, 5, !!(setup_setting.B & SETUP_B_SCROLL), 3);
	
	setup_new_value(6, 9, !!(setup_setting.B & SETUP_B_MARGINBELL), 4);
	setup_new_value(6, 10, !!(setup_setting.B & SETUP_B_KEYCLICK), 5);
	setup_new_value(6, 11, !!(setup_setting.B & SETUP_B_MODE), 6);
	setup_new_value(6, 12, !!(setup_setting.B & SETUP_B_AUTO_X), 7);
	
	setup_new_value(7, 2, !!(setup_setting.B & SETUP_B_SHIFTED), 8);
	setup_new_value(7, 3, !!(setup_setting.B & SETUP_B_WRAPAROUND), 9);
	setup_new_value(7, 4, !!(setup_setting.B & SETUP_B_NEWLINE), 10);
	setup_new_value(7, 5, !!(setup_setting.B & SETUP_B_INTERLACE), 11);
	
	setup_new_value(7, 9, !!(setup_setting.B & SETUP_B_PARITYSENSE), 12);
	setup_new_value(7, 10, !!(setup_setting.B & SETUP_B_PARITY), 13);
	setup_new_value(7, 11, !!(setup_setting.B & SETUP_B_BPC), 14);
	setup_new_value(7, 12, !!(setup_setting.B & SETUP_B_POWER), 15);
}

void setup_A_refresh()
{
	
}

void setup_new_value(row_t row, col_t col, bool_t val, uint8_t value_no)
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
