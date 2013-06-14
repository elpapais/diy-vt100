#ifndef _UART_H_
#define _UART_H_

#include <common.h>
#include <cqueue.h>
#include <hardware/usciA0.h>

extern struct __cqueue uart_rx;
extern struct __cqueue uart_tx;
extern struct __cqueue *uart_tx_ptr;

void uart_init();

void uart_send(const uint8_t data);
void uart_send_uint8(uint8_t val);

#define uart_hardware_enable() usciA0_enable()
#define uart_hardware_disable() usciA0_disable()

#define uart_rx_count() (uart_rx.count)
#define uart_rx_pop() 	(cqueue_pop(&uart_rx))
#define uart_rx_push(data) (cqueue_push(&uart_rx, data))

#define uart_tx_count() (uart_tx_ptr->count)
#define uart_tx_pop()	(cqueue_pop(uart_tx_ptr))
#define uart_tx_push(data) (cqueue_push(uart_tx_ptr, data))

#define uart_send_escape() uart_send(ASCII_ESCAPE)
inline void uart_send_enter();

#define uart_loopback_enable() (uart_tx_ptr = &uart_rx)
#define uart_loopback_disable() (uart_tx_ptr = &uart_tx)

/* uart speed related */
#define UART_SPEED_COUNT USCIA_SPEED_SIZE
#define UART_SPEED_STRING_LENGTH USCIA_SPEED_VALUE_STR_LENGTH
#define uart_speed_get(i) usciA0_speed_get(i)

#endif
