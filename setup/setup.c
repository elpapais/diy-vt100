#include <setup.h>
#include <uart.h>
#include <vt100/state.h>
#include <hardware/timer1_A3.h>

struct __setup_setting
setup_setting;

bool_t setup_show;

const struct __vt100_char buffer_setupA[VT100_HEIGHT][VT100_WIDTH] =  
{
	{{'S', VT100_CHAR_PROP_DOUBLE_WIDTH|VT100_CHAR_PROP_DOUBLE_HEIGHT_TOP}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'A'}},
	{{'S', VT100_CHAR_PROP_DOUBLE_WIDTH|VT100_CHAR_PROP_DOUBLE_HEIGHT_BOTTOM}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'A'}},
	{},
	{{'T', VT100_CHAR_PROP_UNDERLINE}, {'O', VT100_CHAR_PROP_UNDERLINE}, {' ', VT100_CHAR_PROP_UNDERLINE}, {'E', VT100_CHAR_PROP_UNDERLINE}, {'X', VT100_CHAR_PROP_UNDERLINE}, {'I', VT100_CHAR_PROP_UNDERLINE}, {'T', VT100_CHAR_PROP_UNDERLINE}, {' ', VT100_CHAR_PROP_UNDERLINE}, {'P', VT100_CHAR_PROP_UNDERLINE}, {'R', VT100_CHAR_PROP_UNDERLINE}, {'E', VT100_CHAR_PROP_UNDERLINE}, {'S', VT100_CHAR_PROP_UNDERLINE}, {'S', VT100_CHAR_PROP_UNDERLINE}, {' ', VT100_CHAR_PROP_UNDERLINE}, {'S', VT100_CHAR_PROP_UNDERLINE}, {'2', VT100_CHAR_PROP_UNDERLINE}}
};

const struct __vt100_char buffer_setupB[VT100_HEIGHT][VT100_WIDTH] =  
{
	{{'S', VT100_CHAR_PROP_DOUBLE_WIDTH|VT100_CHAR_PROP_DOUBLE_HEIGHT_TOP}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'B'}},
	{{'S', VT100_CHAR_PROP_DOUBLE_WIDTH|VT100_CHAR_PROP_DOUBLE_HEIGHT_BOTTOM}, {'E'}, {'T'}, {'-'}, {'U'}, {'P'}, {' '}, {'B'}},
	{{'T', VT100_CHAR_PROP_UNDERLINE}, {'O', VT100_CHAR_PROP_UNDERLINE}, {' ', VT100_CHAR_PROP_UNDERLINE}, {'E', VT100_CHAR_PROP_UNDERLINE}, {'X', VT100_CHAR_PROP_UNDERLINE}, {'I', VT100_CHAR_PROP_UNDERLINE}, {'T', VT100_CHAR_PROP_UNDERLINE}, {' ', VT100_CHAR_PROP_UNDERLINE}, {'P', VT100_CHAR_PROP_UNDERLINE}, {'R', VT100_CHAR_PROP_UNDERLINE}, {'E', VT100_CHAR_PROP_UNDERLINE}, {'S', VT100_CHAR_PROP_UNDERLINE}, {'S', VT100_CHAR_PROP_UNDERLINE}, {' ', VT100_CHAR_PROP_UNDERLINE}, {'S', VT100_CHAR_PROP_UNDERLINE}, {'2', VT100_CHAR_PROP_UNDERLINE}},
	{},
	{{'S'}, {'P'}, {'E'}, {'E'}, {'D'}, {' '}, {'9'}, {'6'}, {'0'}, {'0'} },
	{},
	{{'1'}, {' '}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {' '}, {'2'}, {' '}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE} },
	{{'3'}, {' '}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {' '}, {'4'}, {' '}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE}, {'0', VT100_CHAR_PROP_INVERSE} },
};

void setup_init()
{
	setup_setting.brightness = TIMER1_A3_PWM_INIT;
}

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
