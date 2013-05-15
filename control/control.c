#include <control.h>

const struct __control
control_opensquarebracket[] = 
{
	func_call			('D', vt100_cursor_backward, 1, 1),
	func_call			('B', vt100_cursor_down, 1, 1),
	func_call			('C', vt100_cursor_forward, 1, 1),
	func_call			('A', vt100_cursor_up, 1, 1),
	func_call			('H', vt100_cursor_position, 2, 1),
	func_call			('f', vt100_cursor_position, 2, 1),
	func_call_noparam	('c', vt100_identity),
	func_call			('q', vt100_load_led, VT100_PARAM_QUEUE_SIZE, 0),
	func_call			('r', vt100_set_topbottom_margin, 2, 0),
	func_call_noparam	('y', vt100_invoke_confidence_test),
	func_call			('J', vt100_erase, 1, 0),
	func_call			('K', vt100_erase, 1, 0),
	func_call			('m', vt100_select_attribute, VT100_PARAM_QUEUE_SIZE, 0),
	func_call			('n', vt100_DSR, 1, 0),
	func_call			('x', vt100_report_parameters, 1, 0),
	control_end()
};

const struct __control
control_hash[] =
{
	func_call_noparam	('3', vt100_set_doubleheight_tophalf),
	func_call_noparam	('4', vt100_set_doubleheight_bottomhalf),
	func_call_noparam	('5', vt100_set_doublewidth),
	func_call_noparam	('8', vt100_fill_all_E),
	control_end()
};

const struct __control
control_C1[] = 
{
	control_select		(ASCII_ESCAPE, control_C1),
	func_call_noparam	('Z', vt100_identity),
	control_select		('[', control_opensquarebracket),
	control_select		('#', control_hash),
	func_call_noparam	('=', vt100_keypad_appmode),
	func_call_noparam	('>', vt100_keypad_nummode),
	func_call_noparam	('Z', vt100_identity),
	func_call_noparam	('8', vt100_restore_cursor),
	func_call_noparam	('7', vt100_save_cursor),
	func_call_noparam	('H', vt100_set_horizontal_tabulation),
	func_call			('D', vt100_cursor_down, 1, 1),
	func_call_noparam	('E', vt100_buffer_newrow),
	func_call			('M', vt100_cursor_up, 1, 1),
	func_call_noparam	('c', vt100_to_reset_state),
	control_end()
};

const struct __control
control_C0[] = 
{
	control_select		(ASCII_ESCAPE, control_C1),
	func_call_noparam	(ASCII_BELL, vt100_bell),
	//func_call_noparam(ASCII_ENQ, vt100_identity), is ASCII_ENQ alias of ESC Z ??
	control_end()
};

const struct __control
control_open_smallbracket[] =
{
	control_end()
};

const struct __control
control_close_smallbracket[] =
{
	control_end()
};

static struct __control
*current_control = (struct __control *)control_C0;

void
control()
{
	static struct __control
	*i;

	vt100.data = UCA0RXBUF;

	/* search for recv in __block table */
	for(i=current_control; i->cb; i++)
	{
		if(i->ch != vt100.data)
		{
			continue;
		}
		
		if(i->cb == (callback_t)1)
		{
			current_control = (struct __control *)i->arg.select;
		}
		else
		{
			vt100_param_default(i->arg.param.pcount, i->arg.param.pdefault);
			i->cb();
			vt100_param_reset();
		}
		
		break;
	}
	
	/* is it not found */
	if(i->cb == 0)
	{
		/* if we are at start state, store it in buffer */
		if(current_control == control_C0)
		{
			vt100_buffer_putchar();
		}
		
		/* assuming this as paramter */
		else if(!vt100_param_add())
		{
			return;
		}
	}
	else if(i->cb != (callback_t)1)
	{
		/* at the end of execution, revert to start state, | ignore unknown paramters */
		current_control = (struct __control *)control_C0;
	}
	
	vt100_refresh();
}
