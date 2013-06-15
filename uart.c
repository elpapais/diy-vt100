#include <diy-vt100/setting.h>
#include <diy-vt100/uart.h>

void uart_send_uint8(uint8_t val)
{
	uint8_t tmp = val / 100;
	
	if(tmp)
	{
		uart_send('0' + tmp);
		val -= tmp * 100;
	}

	tmp = val / 10;
	if(tmp)
	{
		uart_send('0' + tmp);
		val -= tmp * 10;
	}
	
	uart_send('0' + val);
}

inline void uart_send_enter()
{
	uart_send(ASCII_CR);
	
	if(setting_ishigh(SETTING_LNM))
	{
		uart_send(ASCII_LF);
	}
}
