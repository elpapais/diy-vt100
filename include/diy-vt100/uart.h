#ifndef UART_H
#define UART_H

#include <diy-vt100/common.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/hardware/uart.h>

typedef struct
{
	uint8_t bitrate[6];
	uint8_t value[4];
} uartspeed_t;

extern const uartspeed_t uart_speed[UART_SPEED_COUNT];
extern const uint8_t uart_clkmul;

void uart_init(const bool_t parity,const bool_t parity_sense,
						const uint8_t rx_speed, const uint8_t tx_speed);

typedef enum
{
	DISABLE,
	ENABLE
}	
uartlopbk_t;

void uart_loopback(uartlopbk_t);
bool_t uart_disconnected(void);

void uart_send(const uint8_t data);
void uart_send_uint8(uint8_t val);
inline void uart_send_escape(void);
inline void uart_send_enter(void);
void uart_send_array(const uint8_t *arr, const uint8_t size);

inline void uart_send_enter(void)
{
	uart_send(ASCII_CR);

	if(parm_setting.bits.LNM)
	{
		uart_send(ASCII_LF);
	}
}

inline void uart_send_escape(void)
{
	uart_send(ASCII_ESCAPE);
}

#endif
