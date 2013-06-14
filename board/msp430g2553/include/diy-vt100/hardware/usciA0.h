#ifndef _HW_USCIA_H_
#define _HW_USCIA_H_

#include <diy-vt100/common.h>
#include <diy-vt100/vt100/buffer.h>

#define USCIA_SPEED_SIZE 7
#define USCIA_SPEED_VALUE_STR_LENGTH 6

struct __usciA0_speed
{
	uint8_t BR0;
	uint8_t BR1;
	struct __vt100_char value_str[USCIA_SPEED_VALUE_STR_LENGTH];
};

extern const struct __usciA0_speed usciA0_speed[USCIA_SPEED_SIZE];

#define usciA0_speed_get(i) (usciA0_speed[i].value_str)
#define usciA0_enable() usciA0_init()
#define usciA0_disable() (UCA0CTL1 |= UCSWRST)
#define usciA0_tx_interrupt_enable() (IE2 |= UCA0TXIE)

void usciA0_init();
void usciA0_TX_interrupt() __attribute__((interrupt(USCIAB0TX_VECTOR))); /* USCI_A_TX */
void usciA0_RX_interrupt() __attribute__((interrupt(USCIAB0RX_VECTOR))); /* USCI_A_RX */

#endif
