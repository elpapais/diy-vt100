#ifndef _UART_H_
#define _UART_H_

#include <vt100/param.h>
#include <cqueue.h>
#include <common.h>

void uart_send(const uint8_t data);
void uart_send_uint8(uint8_t val);

#define uart_send_enter() uart_send(ASCII_LF)
#define uart_send_escape() uart_send(ASCII_ESCAPE)

extern struct __cqueue uart_rx;
extern struct __cqueue uart_tx;

#endif
