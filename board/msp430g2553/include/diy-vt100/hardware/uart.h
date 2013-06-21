#ifndef _HW_USCIA_H_
#define _HW_USCIA_H_

#include <diy-vt100/common.h>
#include <diy-vt100/vt100/buffer.h>

#define UART_SPEED_SIZE 7
#define UART_SPEED_VALUE_STR_LENGTH 6

struct __usciA0_speed
{
	uint8_t BR0;
	uint8_t BR1;
	struct __vt100_char value_str[UART_SPEED_VALUE_STR_LENGTH];
};

extern const struct __usciA0_speed usciA0_speed[UART_SPEED_SIZE];

#define uart_speed_get(i) (usciA0_speed[i].value_str)

#endif
