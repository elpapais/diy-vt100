#include <diy-vt100/hardware/uart.h>

struct __cqueue
uart_tx, uart_rx, *uart_tx_ptr;

void uart_send(const uint8_t data)
{
	uart_tx_push(data);
	
	/* enable interrupt if it was disabled due to empty cqueue */
	usciA0_tx_interrupt_enable();
}
