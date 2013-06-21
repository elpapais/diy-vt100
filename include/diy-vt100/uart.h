#ifndef _UART_H_
#define _UART_H_

#include <diy-vt100/common.h>
#include <diy-vt100/hardware/uart.h>
#include <diy-vt100/cqueue.h>

extern struct __cqueue uart_tx;
extern struct __cqueue uart_rx;

void uart_init();
void uart_send(const uint8_t data);
void uart_send_uint8(uint8_t val);
void uart_loopback_disable();
void uart_loopback_enable();

inline void uart_send_escape();
inline void uart_send_enter();

#endif
