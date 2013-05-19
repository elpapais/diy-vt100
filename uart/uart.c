#include <uart.h>

struct __cqueue
uart_cqueue_tx = 
{
	0, 0
};

struct __cqueue
uart_cqueue_rx = 
{
	0, 0
};

void uart_send(const uint8_t data)
{
	cqueue_push(&uart_cqueue_tx, data);
	
	/* enable interrupt if it was disabled due to empty cqueue */
	IE2 |= UCA0TXIE;
}

void uart_send_int(uint8_t val)
{
	/* send the number from heighest digit place to lowest digit place (recursively) */
	if(val > 9)
	{
		uart_send_int(val/10);
		val %= 10;
	}
	
	uart_send('0' + val);
}

void uart_send_string(char *str)
{
	while(*str)
	{
		uart_send(*str);
		str++;
	}
}

void uart_send_param(uint8_t before, uint8_t after, uint8_t default_value)
{
	uint8_t i = 0;
	
	uart_send(ASCII_ESCAPE);
	uart_send(before);
	
	while(i < vt100_param_getcount())
	{
		if(vt100_param_get(i) != default_value)
		{
			uart_send_int(vt100_param_get(i));
		}
		
		if(++i < vt100_param_getcount())
		{
			uart_send(VT100_PARAM_DELIMITER);
		}
	}
	
	uart_send(after);
}
