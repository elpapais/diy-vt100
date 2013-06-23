#include <diy-vt100/setting.h>
#include <diy-vt100/uart.h>

cqueue_t uart_tx, uart_rx;

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

void uart_send_array(const uint8_t *arr, const uint8_t size)
{
	for(uint8_t i=0; i < size; i++)
	{
		uart_send(arr[i]);
	}
}
