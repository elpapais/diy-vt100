#include <uart.h>

void
uart_init()
{
	/* Configure ports */
    P1SEL = BIT1 + BIT2;                // P1.1 = RXD, P1.2=TXD
    P1SEL2= BIT1 + BIT2;                // P1.1 = RXD, P1.2=TXD
    
    /* Initialize USCI registers */
    UCA0CTL1 |= UCSSEL_2;
    
    /* 1MHz / 9600 = 104 */
    UCA0BR0 = 104;
    UCA0BR1 = 0;
    
	UCA0MCTL = UCBRS0;
	
	/* Clear UCSWRST flag (Initialize USCI state machine) */
	UCA0CTL1 &= ~UCSWRST;

	/* Enable interrupts */
	IE2 |= UCA0RXIE;

	/* RX interrupt goes to control() */
}

void
uart_send(uint8_t data)
{
	/* Wait until USCI_A0 TX buffer is ready */
    while (!(IFG2 & UCA0TXIFG));

    /* Send the byte */
    UCA0TXBUF = data;
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

	/* reusing "before" variable */
	
	while(before < vt100_param_getcount())
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
