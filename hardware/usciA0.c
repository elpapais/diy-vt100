#include <hardware/usciA0.h>
#include <hardware/usciA0.h>
#include <hardware/flash.h>

#include <cqueue.h>
#include <uart.h>

#define usciA0_speed_collector(brx, ch5, ch4, ch3, ch2, ch1, ch0) \
			{(uint8_t)(brx & 0x00FF), (uint8_t)(brx >> 8), {{ch5}, {ch4}, {ch3}, {ch2}, {ch1}, {ch0}}}

/* SMCLK @ 4MHz */
const struct __usciA0_speed usciA0_speed[USCIA_SPEED_SIZE] =
{
	usciA0_speed_collector(416, '9','6','0','0', 0,  0),
	usciA0_speed_collector(208, '1','9','2','0','0', 0),
	usciA0_speed_collector(104, '3','8','4','0','0', 0),
	usciA0_speed_collector(071, '5','6','0','0','0', 0),
	usciA0_speed_collector(034, '1','1','5','2','0','0'),
	usciA0_speed_collector(031, '1','2','8','0','0','0'),
	usciA0_speed_collector(015, '2','5','6','0','0','0')
};

void usciA0_init()
{
	/* Configure ports */
	P1SEL = BIT1 + BIT2; /* P1.1 = RXD, P1.2=TXD */
	P1SEL2= BIT1 + BIT2; /* P1.1 = RXD, P1.2=TXD */

	/* Initialize USCI registers */
	UCA0CTL1 = UCSSEL_2;
	
	if(flash_setting_read(SETTING_PARITY))
	{
		/* enable parity */
		UCA0CTL1 |= UCPEN;
		
		/* set parity to EVEN */
		if(flash_setting_read(SETTING_PARITYSENSE))
		{
			/* EVEN parity */
			UCA0CTL1 |= UCPAR;
		}
	}
	
	UCA0BR0 = usciA0_speed[flash_setting.speed].BR0;
	UCA0BR1 = usciA0_speed[flash_setting.speed].BR1;
	
	UCA0MCTL = UCBRS_6;

	/* Clear UCSWRST flag (Initialize USCI state machine) */
	UCA0CTL1 &= ~UCSWRST;

	/* Enable interrupts (UCA0TXIE will be enabled by uart_send) */
	IE2 = UCA0RXIE;

	/* RX interrupt goes to usci0_RX_interrupt() */
	/* TX interrupt goes to usci0_TX_interrupt() */
}

/* push received data to uart buffer */
void usciA0_RX_interrupt()
{
	uart_rx_push(UCA0RXBUF);
	/* TODO: XON/XOFF sending for preventing overflow on when count == 16 */
	
	/* exit sleep mode to refresh screen */
	__bic_status_register_on_exit(LPM1_bits);
}

void usciA0_TX_interrupt()
{
	if(uart_tx_count())
	{
		UCA0TXBUF = uart_tx_pop();
	}
	else
	{
		IE2 &= ~UCA0TXIE;
	}
}
