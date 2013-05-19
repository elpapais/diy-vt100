#ifndef _INTERRUPT_USCI0_H_
#define _INTERRUPT_USCI0_H_

#include <common.h>
#include <cqueue.h>
#include <uart.h>

#define usci0_init() uart_init()

void usci0_transmit_interrupt() __attribute__((interrupt(USCIAB0TX_VECTOR))); /* USCI_A_RX */
void usci0_receive_interrupt() __attribute__((interrupt(USCIAB0RX_VECTOR))); /* USCI_A_RX */

#endif
