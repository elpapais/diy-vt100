#include <setup.h>
#include <uart.h>
#include <vt100/state.h>
#include <vt100/buffer.h>
#include <setting.h>

bool_t setup_show;

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
