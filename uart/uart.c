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

void
uart_init()
{
	/* Configure ports */
    P1SEL = BIT1 + BIT2;                // P1.1 = RXD, P1.2=TXD
    P1SEL2= BIT1 + BIT2;                // P1.1 = RXD, P1.2=TXD
    
    /* Initialize USCI registers */
    UCA0CTL1 |= UCSSEL_2;
    
    /* SMCLK @ 4MHz , BR 9600 */
    UCA0BR0 = 0x00FF & 416;
    UCA0BR1 = 416 >> 8;
    
	UCA0MCTL = UCBRS_6;
	
	/* Clear UCSWRST flag (Initialize USCI state machine) */
	UCA0CTL1 &= ~UCSWRST;

	/* Enable interrupts (UCA0TXIE will be enabled by uart_send) */
	IE2 = UCA0RXIE;

	/* RX interrupt goes to uart_queue_push() */
}

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


