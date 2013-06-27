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
void uart_send_array(const uint8_t *arr, const uint8_t size);

inline void uart_send_return(void)
{
	uart_send(ASCII_CR);

	if(parm_setting.bits.LNM)
	{
		uart_send(ASCII_LF);
	}
}

/* === KEYPAD === */

inline void __uart_send_keypad_mode(const uint8_t ascii, const uint8_t esc_seq)
{
	if(parm_setting.bits.DECKPAM)
	{
		uart_send(ASCII_ESCAPE);
		uart_send(parm_setting.bits.DECANM ? 'O' : '?');
		uart_send(esc_seq);
	}
	else
	{
		uart_send(ascii);
	}
}

inline void uart_send_keypad_num(const uint8_t num)
{
	__uart_send_keypad_mode('0' + num, 'p' + num);
}

inline void uart_send_keypad_dot()
{
	__uart_send_keypad_mode('.', 'n');
}

inline void uart_send_keypad_dash()
{
	__uart_send_keypad_mode('-', 'm');
}

inline void uart_send_keypad_comma()
{
	__uart_send_keypad_mode(',', 'l');
}

inline void uart_send_keypad_enter()
{
	if(parm_setting.bits.DECKPAM)
	{
		uart_send(ASCII_ESCAPE);
		uart_send(parm_setting.bits.DECANM ? 'O' : '?');
		uart_send('M');
	}
	else
	{
		uart_send_return();
	}
}

#define PF1 'P'
#define PF2 'Q'
#define PF3 'R'
#define PF4 'S'

inline void uart_send_keypad_pfn(uint8_t code)
{
	uart_send(ASCII_ESCAPE);
	
	if(parm_setting.bits.DECANM)
	{
		uart_send('O');
	}
	
	uart_send(code);
}

/* === ARROW === */

#define UP 		'A'
#define DOWN 	'B'
#define RIGHT 	'C'
#define LEFT 	'D'

inline void uart_send_arrow(const uint8_t code)
{
	uart_send(ASCII_ESCAPE);
	uart_send(parm_setting.bits.DECANM ?
					(parm_setting.bits.DECCKM ? 'O' : '[') : '?' );
	
	uart_send(code);
}

#endif
