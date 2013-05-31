#ifndef _HARDWARE_USCIA_H_
#define _HARDWARE_USCIA_H_

#include <common.h>

#define usciA_enable() usciA_init()
#define usciA_disable() UCA0CTL1 |= UCSWRST

/* used in uart.c */
#define usciA_tx_interrupt_enable() (IE2 |= UCA0TXIE)

void usciA_init();
void usciA_TX_interrupt() __attribute__((interrupt(USCIAB0TX_VECTOR))); /* USCI_A_TX */
void usciA_RX_interrupt() __attribute__((interrupt(USCIAB0RX_VECTOR))); /* USCI_A_RX */

#endif
