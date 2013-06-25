#ifndef HW_UART_H
#define HW_UART_H

#include <diy-vt100/hardware/cqueue.h>

extern cqueue_t uart_tx;
extern cqueue_t uart_rx;

#define UART_SPEED_COUNT 2

#endif
