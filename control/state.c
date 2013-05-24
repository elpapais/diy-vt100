#include <control.h>

const struct __control
control_opensquarebracket[] = //[
{
	control_select		(ASCII_ESCAPE, control_C1),
	func_call			('D', vt100_cursor_backward, 1, 1),
	func_call			('B', vt100_cursor_down, 1, 1),
	func_call			('C', vt100_cursor_forward, 1, 1),
	func_call			('A', vt100_cursor_up, 1, 1),
	func_call			('H', vt100_cursor_position, 2, 1),
	func_call			('f', vt100_cursor_position, 2, 1),
	func_call_noparam	('c', vt100_report_identity),
	func_call			('q', vt100_led_load, VT100_PARAM_QUEUE_SIZE, 0),
	func_call			('r', vt100_margin_set_topbottom, 2, 0),
	func_call_noparam	('y', vt100_invoke_confidence_test),
	func_call			('J', vt100_buffer_erase, 1, 0),
	func_call			('K', vt100_buffer_erase, 1, 0),
	func_call			('m', vt100_attribute_select, VT100_PARAM_QUEUE_SIZE, 0),
	func_call			('n', vt100_report_DSR, 1, 0),
	func_call			('x', vt100_report_parameters, 1, 0),
	func_call			('g', vt100_tabulation_clear, 1,0),
	control_end()
};

const struct __control
control_hash[] = //#
{
	control_select		(ASCII_ESCAPE, control_C1),
	func_call_noparam	('3', vt100_double_height_tophalf),
	func_call_noparam	('4', vt100_double_height_bottomhalf),
	func_call_noparam	('5', vt100_double_width),
	func_call_noparam	('8', vt100_buffer_fill_E),
	control_end()
};

const struct __control
control_C1[] = 
{
	control_select		(ASCII_ESCAPE, control_C1),
	control_select		('[', control_opensquarebracket),
	control_select		('#', control_hash),
	func_call_noparam	('Z', vt100_report_identity),
	func_call_noparam	('=', vt100_keypad_appmode),
	func_call_noparam	('>', vt100_keypad_nummode),
	func_call_noparam	('8', vt100_cursor_restore),
	func_call_noparam	('7', vt100_cursor_save),
	func_call_noparam	('H', vt100_tabulation_set),
	func_call_noparam	('D', vt100_cursor_down_with_scrollup),
	func_call_noparam	('E', vt100_buffer_newrow),
	func_call_noparam	('M', vt100_cursor_up_with_scrolldown),
	func_call_noparam	('c', vt100_to_reset_state),
	control_end()
};

const struct __control
control_C0[] = 
{
	control_select		(ASCII_ESCAPE, control_C1),
	func_call_noparam	(ASCII_BELL, vt100_audio_bell),
	func_call_noparam	(ASCII_TAB, vt100_tabulation_goto_next),
	func_call			(ASCII_BS, vt100_cursor_backward, 1, 1),
	/* TODO: LNM: newline mode, no mode, default applied */
	func_call_noparam	(ASCII_LF, vt100_buffer_newrow),
	char_ignore			(ASCII_CR),
	char_ignore			(ASCII_DEL),
	char_ignore			(ASCII_NULL),
	//func_call_noparam(ASCII_ENQ, vt100_identity), is ASCII_ENQ alias of ESC Z ??
	control_end()
};

const struct __control
control_open_smallbracket[] =
{
	control_select		(ASCII_ESCAPE, control_C1),
	control_end()
};

const struct __control
control_close_smallbracket[] =
{
	control_select		(ASCII_ESCAPE, control_C1),
	control_end()
};
