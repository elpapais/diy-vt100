#ifndef _UART_H_
#define _UART_H_

#include <vt100/vt100.h>
#include <common.h>

void uart_init();

#define uart_send_ESCseq(str) uart_send(ASCII_ESCAPE);uart_send_string(str)
void uart_send(uint8_t send);
void uart_send_int(uint8_t val);
void uart_send_string(char *str);
void uart_send_param(uint8_t before, uint8_t after, uint8_t default_value);

#endif
