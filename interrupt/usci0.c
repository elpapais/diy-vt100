#include <interrupt/usci0.h>

/* push received data to uart buffer */
void usci0_receive_interrupt()
{
	uint8_t d = UCA0RXBUF;
	
	cqueue_push(&uart_cqueue_rx, d);
	uart_send(d);
	/* TODO: XON/XOFF sending for preventing overflow on when count == 32 */
}

void usci0_transmit_interrupt()
{
	if(cqueue_count(uart_cqueue_tx))
	{
		UCA0TXBUF = cqueue_pop(&uart_cqueue_tx);
	}
	else
	{
		IE2 &= ~UCA0TXIE;
	}
}
