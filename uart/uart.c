#include <uart.h>

struct __cqueue
uart_tx, uart_rx;

void uart_send(const uint8_t data)
{
	cqueue_push(&uart_tx, data);
	
	/* enable interrupt if it was disabled due to empty cqueue */
	IE2 |= UCA0TXIE;
}

void uart_send_uint8(uint8_t val)
{
	/* send the number from heighest digit place to lowest digit place (recursively) */
	if(val > 9)
	{
		uart_send_uint8(val/10);
		val %= 10;
	}
	
	uart_send('0' + val);
}
