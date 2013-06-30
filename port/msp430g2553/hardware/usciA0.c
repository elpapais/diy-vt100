#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/msp430g2553/cqueue.h>
#include <diy-vt100/msp430g2553/ic_74xx595.h>

void usciA0_RX_interrupt() __attribute__((interrupt(USCIAB0RX_VECTOR)));
void usciA0_TX_interrupt() __attribute__((interrupt(USCIAB0TX_VECTOR)));

cqueue_t uart_tx, uart_rx;

const uint8_t uart_clkmul = '1';

const uartspeed_t uart_speed[UART_SPEED_COUNT] = 
{
	{{4, '9', '6', '0', '0'}, {3, '1', '1', '2'}},
	{{5, '1', '9', '2', '0', '0'}, {3, '1', '2', '0'}}
};

void usciA0_init(void)
{
#define usciA0_speed_collector(brx) {(uint8_t)(brx & 0x00FF), (uint8_t)(brx >> 8)}
	const static struct
	{
		uint8_t BR0;
		uint8_t BR1;
	}
	usciA0_speed[UART_SPEED_COUNT] =
	{
		usciA0_speed_collector(416),
		usciA0_speed_collector(208),
		//usciA0_speed_collector(104, '3','8','4','0','0', 0),
		//usciA0_speed_collector(071, '5','6','0','0','0', 0),
		//usciA0_speed_collector(034, '1','1','5','2','0','0'),
		//usciA0_speed_collector(031, '1','2','8','0','0','0'),
		//usciA0_speed_collector(015, '2','5','6','0','0','0')
	};
	
	/* Configure ports */
	P1SEL = BIT1 + BIT2; /* P1.1 = RXD, P1.2=TXD */
	P1SEL2= BIT1 + BIT2; /* P1.1 = RXD, P1.2=TXD */

	/* Initialize USCI registers */
	UCA0CTL1 = UCSSEL_2;

	if(parm_setting.bits.PARITY)
	{
		/* enable parity */
		UCA0CTL1 |= UCPEN;

		/* set parity to EVEN */
		if(parm_setting.bits.PARITYSENSE)
		{
			/* EVEN parity */
			UCA0CTL1 |= UCPAR;
		}
	}

	UCA0BR0 = usciA0_speed[parm_setting.uart_rx].BR0;
	UCA0BR1 = usciA0_speed[parm_setting.uart_rx].BR1;

	UCA0MCTL = UCBRS_6;

	/* Clear UCSWRST flag (Initialize USCI state machine) */
	UCA0CTL1 &= ~UCSWRST;

	/* Enable interrupts (UCA0TXIE will be enabled by uart_send) */
	IE2 = UCA0RXIE;

	/* RX interrupt goes to usci0_RX_interrupt() */
	/* TX interrupt goes to usci0_TX_interrupt() */
}

/* push received data to uart buffer */
void usciA0_RX_interrupt(void)
{
	cqueue_push(&uart_rx, __read(UCA0STAT, UCPE) ? 176 : UCA0RXBUF);

	/* exit sleep mode to refresh screen */
	__bic_status_register_on_exit(LPM1_bits);
}

void usciA0_TX_interrupt(void)
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

void uart_send(const uint8_t data)
{
	if(! setting.bits.XOFFED)
	{
		/* enable transmission */
		IE2 |= UCA0TXIE;
	}
	
	if(uart_tx.count < CQUEUE_SIZE)
	{
		cqueue_push(&uart_tx, data);
		
		ic_74xx595.led_kbdlock = FALSE;
	}
	else
	{
		ic_74xx595.led_kbdlock = TRUE;
	}
}

void uart_loopback(edable_t ed)
{
	switch(ed)
	{
		case ENABLE:
			__high(UCA0STAT, UCLISTEN);
		break;
		
		case DISABLE:
			__low(UCA0STAT, UCLISTEN);
		break;
	}
}

bool_t uart_disconnected(void)
{
	return __read(UCA0STAT, UCIDLE);
}
