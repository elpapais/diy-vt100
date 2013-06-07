#include <setup.h>
#include <uart.h>
#include <vt100/state.h>
#include <setting.h>

bool_t setup_show;

const struct __vt100_char setup_buffer_A[VT100_HEIGHT][VT100_WIDTH] =  
{
	{{'S', VT100_CHAR_PROP_ROW_DOUBLE_WIDTH|VT100_CHAR_PROP_ROW_DOUBLE_HEIGHT_TOP|VT100_CHAR_PROP_ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'A'}},
	{{'S', VT100_CHAR_PROP_ROW_DOUBLE_WIDTH|VT100_CHAR_PROP_ROW_DOUBLE_HEIGHT_BOTTOM|VT100_CHAR_PROP_ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'A'}},
	{{'T', VT100_CHAR_PROP_DATA_UNDERLINE|VT100_CHAR_PROP_ROW_TOUCH}, {'O', VT100_CHAR_PROP_DATA_UNDERLINE}, {' ', VT100_CHAR_PROP_DATA_UNDERLINE}, {'E', VT100_CHAR_PROP_DATA_UNDERLINE}, {'X', VT100_CHAR_PROP_DATA_UNDERLINE}, {'I', VT100_CHAR_PROP_DATA_UNDERLINE}, {'T', VT100_CHAR_PROP_DATA_UNDERLINE}, {' ', VT100_CHAR_PROP_DATA_UNDERLINE}, {'P', VT100_CHAR_PROP_DATA_UNDERLINE}, {'R', VT100_CHAR_PROP_DATA_UNDERLINE}, {'E', VT100_CHAR_PROP_DATA_UNDERLINE}, {'S', VT100_CHAR_PROP_DATA_UNDERLINE}, {'S', VT100_CHAR_PROP_DATA_UNDERLINE}, {' ', VT100_CHAR_PROP_DATA_UNDERLINE}, {'S', VT100_CHAR_PROP_DATA_UNDERLINE}, {'2', VT100_CHAR_PROP_DATA_UNDERLINE}},
	{{0, VT100_CHAR_PROP_ROW_TOUCH}},
	{{0, VT100_CHAR_PROP_ROW_TOUCH}},
	{{0, VT100_CHAR_PROP_ROW_TOUCH}},
	{{0, VT100_CHAR_PROP_ROW_TOUCH}},
	{{'1', VT100_CHAR_PROP_ROW_TOUCH|VT100_CHAR_PROP_ROW_TOUCH}, {'2'}, {'3'}, {'4'}, {'5'}, {'6'}, {'7'}, {'8'}, {'9'}, {'0'}, {'1', VT100_CHAR_PROP_DATA_INVERSE}, {'2', VT100_CHAR_PROP_DATA_INVERSE}, {'3', VT100_CHAR_PROP_DATA_INVERSE}, {'4', VT100_CHAR_PROP_DATA_INVERSE}, {'5', VT100_CHAR_PROP_DATA_INVERSE}, {'6', VT100_CHAR_PROP_DATA_INVERSE}}
};

const struct __vt100_char setup_buffer_B[VT100_HEIGHT][VT100_WIDTH] =  
{
	{{'S', VT100_CHAR_PROP_ROW_DOUBLE_WIDTH|VT100_CHAR_PROP_ROW_DOUBLE_HEIGHT_TOP|VT100_CHAR_PROP_ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'B'}},
	{{'S', VT100_CHAR_PROP_ROW_DOUBLE_WIDTH|VT100_CHAR_PROP_ROW_DOUBLE_HEIGHT_BOTTOM|VT100_CHAR_PROP_ROW_TOUCH}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'B'}},
	{{'T', VT100_CHAR_PROP_DATA_UNDERLINE|VT100_CHAR_PROP_ROW_TOUCH}, {'O', VT100_CHAR_PROP_DATA_UNDERLINE}, {' ', VT100_CHAR_PROP_DATA_UNDERLINE}, {'E', VT100_CHAR_PROP_DATA_UNDERLINE}, {'X', VT100_CHAR_PROP_DATA_UNDERLINE}, {'I', VT100_CHAR_PROP_DATA_UNDERLINE}, {'T', VT100_CHAR_PROP_DATA_UNDERLINE}, {' ', VT100_CHAR_PROP_DATA_UNDERLINE}, {'P', VT100_CHAR_PROP_DATA_UNDERLINE}, {'R', VT100_CHAR_PROP_DATA_UNDERLINE}, {'E', VT100_CHAR_PROP_DATA_UNDERLINE}, {'S', VT100_CHAR_PROP_DATA_UNDERLINE}, {'S', VT100_CHAR_PROP_DATA_UNDERLINE}, {' ', VT100_CHAR_PROP_DATA_UNDERLINE}, {'S', VT100_CHAR_PROP_DATA_UNDERLINE}, {'2', VT100_CHAR_PROP_DATA_UNDERLINE}},
	{{0, VT100_CHAR_PROP_ROW_TOUCH}},
	{{'T', VT100_CHAR_PROP_ROW_TOUCH}, {' '}, {'S'}, {'P'}, {'E'}, {'E'}, {'D'}, {' '}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'} },
	{{'R', VT100_CHAR_PROP_ROW_TOUCH}, {' '}, {'S'}, {'P'}, {'E'}, {'E'}, {'D'}, {' '}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'}, {'*'} },
	{{'1', VT100_CHAR_PROP_ROW_TOUCH}, {' '}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {' '}, {'2'}, {' '}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE} },
	{{'3', VT100_CHAR_PROP_ROW_TOUCH}, {' '}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {' '}, {'4'}, {' '}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE}, {'0', VT100_CHAR_PROP_DATA_INVERSE} },
};

void setup()
{
	setup_show ^= TRUE;
	
	if(setup_show)
	{
		/* enter setup */
		uart_hardware_disable();
		uart_loopback_enable();
		state_current = (struct __state *)setup_state_type;
		setup_type_current = 'B';
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
