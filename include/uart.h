#ifndef _UART_H_
#define _UART_H_

#include <common.h>
#include <cqueue.h>
#include <hardware/usciA.h>

extern struct __cqueue uart_rx;
extern struct __cqueue uart_tx;
extern struct __cqueue *uart_tx_ptr;

void uart_init();

void uart_send(const uint8_t data);
void uart_send_uint8(uint8_t val);

#define uart_hardware_enable() usciA_enable()
#define uart_hardware_disable() usciA_disable()

#define uart_rx_count() (uart_rx.count)
#define uart_rx_pop() 	(cqueue_pop(&uart_rx))
#define uart_rx_push(data) (cqueue_push(&uart_rx, data))

#define uart_tx_count() (uart_tx_ptr->count)
#define uart_tx_pop()	(cqueue_pop(uart_tx_ptr))
#define uart_tx_push(data) (cqueue_push(uart_tx_ptr, data))

#define uart_send_enter() uart_send(ASCII_LF)
#define uart_send_escape() uart_send(ASCII_ESCAPE)

#define uart_loopback_enable() (uart_tx_ptr = &uart_rx)
#define uart_loopback_disable() (uart_tx_ptr = &uart_tx)

#endif
