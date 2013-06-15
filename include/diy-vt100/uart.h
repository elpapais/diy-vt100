#ifndef _UART_H_
#define _UART_H_

#include <diy-vt100/common.h>
#include <diy-vt100/hardware/uart.h>

#define uart_send_escape() uart_send(ASCII_ESCAPE)
inline void uart_send_enter();

void uart_send(const uint8_t data);
void uart_send_uint8(uint8_t val);

#endif
