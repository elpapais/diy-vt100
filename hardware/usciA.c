#include <hardware/usciA.h>

void usciA_init()
{
	/* Configure ports */
	P1SEL = BIT1 + BIT2; /* P1.1 = RXD, P1.2=TXD */
	P1SEL2= BIT1 + BIT2; /* P1.1 = RXD, P1.2=TXD */

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

	/* RX interrupt goes to usci0_RX_interrupt() */
	/* TX interrupt goes to usci0_TX_interrupt() */
}

/* push received data to uart buffer */
void usciA_RX_interrupt()
{
	cqueue_push(&uart_rx, UCA0RXBUF);
	/* TODO: XON/XOFF sending for preventing overflow on when count == 16 */
	
	/* exit sleep mode to refresh screen */
	__bic_status_register_on_exit(LPM1_bits);
}

void usciA_TX_interrupt()
{
	if(uart_tx.count)
	{
		UCA0TXBUF = cqueue_pop(&uart_tx);
	}
	else
	{
		IE2 &= ~UCA0TXIE;
	}
}
