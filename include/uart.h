#ifndef _UART_H_
#define _UART_H_

#include <vt100/param.h>
#include <cqueue.h>
#include <common.h>

void uart_init();

#define uart_send_ESCseq(str) uart_send(ASCII_ESCAPE);uart_send_string(str)

void uart_send(const uint8_t data);
void uart_send_int(uint8_t val);
void uart_send_string(char *str);
void uart_send_param(uint8_t before, uint8_t after, uint8_t default_value);

extern struct __cqueue uart_cqueue_rx;
extern struct __cqueue uart_cqueue_tx;

#endif
