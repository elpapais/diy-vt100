#include <diy-vt100/msp430g2553/spi.h>
#include <diy-vt100/common.h>

#define UCB0CLK BIT5
#define UCB0SIMO BIT7
//#define UCB0SOMI BIT6

void spi_init(void)
{
	UCB0CTL1 = UCSWRST;
	
	UCB0CTL0 = UCCKPH + UCMST + UCSYNC + UCMSB;
	
	UCB0BR0 = 1;
	UCB0BR1 = 0;
	
	__high(P1SEL, UCB0CLK | UCB0SIMO);
	__high(P1SEL2, UCB0CLK | UCB0SIMO);
	
	/* SMCLK */
	UCB0CTL1 = UCSSEL_2;
	
	/* spi_transfer9 init */
	__high(P1DIR, UCB0CLK | UCB0SIMO);
	__low(P1OUT, UCB0CLK | UCB0SIMO);
}

void spi_send(const uint8_t data)
{
	UCB0TXBUF = data;
	
	/* wait while busy */
	while(UCB0STAT & UCBUSY);
}

void spi_send9(uint16_t data)
{
	__low(P1SEL2, UCB0CLK | UCB0SIMO);
	__low(P1SEL, UCB0CLK | UCB0SIMO);
	
	/* Perform single-bit transfer */
	if (data & BIT8)
	{
		P1OUT |= UCB0SIMO;
		__high(P1OUT, UCB0SIMO);
	}
	
	__high(P1OUT, UCB0CLK);
	__low(P1OUT, UCB0CLK | UCB0SIMO);
	
	/* Restore port states and continue with 8-bit SPI */
	__high(P1SEL, UCB0CLK | UCB0SIMO);
	__high(P1SEL2, UCB0CLK | UCB0SIMO);

	spi_send((uint8_t)(data & 0xFF));
}
