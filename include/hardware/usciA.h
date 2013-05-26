#ifndef _HARDWARE_USCIA_H_
#define _HARDWARE_USCIA_H_

#include <common.h>
#include <cqueue.h>
#include <uart.h>

void usciA_init();
void usciA_TX_interrupt() __attribute__((interrupt(USCIAB0TX_VECTOR))); /* USCI_A_TX */
void usciA_RX_interrupt() __attribute__((interrupt(USCIAB0RX_VECTOR))); /* USCI_A_RX */

#endif
