#ifndef _HARDWARE_USCI0_H_
#define _HARDWARE_USCI0_H_

#include <common.h>
#include <cqueue.h>
#include <uart.h>

void usci0_init();
void usci0_TX_interrupt() __attribute__((interrupt(USCIAB0TX_VECTOR))); /* USCI_A_RX */
void usci0_RX_interrupt() __attribute__((interrupt(USCIAB0RX_VECTOR))); /* USCI_A_RX */

#endif
