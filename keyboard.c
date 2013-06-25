#include <diy-vt100/keyboard.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/bell.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/vt100/misc.h>
#include <diy-vt100/setup.h>

void keyboard_arrow(const kbdarrow_t arrow)
{
	uart_send_escape();
	
	uint8_t map[4] = {'P', 'Q', 'R', 'S'};
	
	if(parm_setting.bits.DECANM)
	{
		uart_send(parm_setting.bits.DECCKM ? 'O' : '[');
	}

	uart_send(map[arrow]);
	
	keyboard_keyclick_sound();
}

void keyboard_other(const uint8_t ascii)
{
	uart_send((setting.bits.KBD_CTRL) ? ((ascii -'@') & ~BIT7) : ascii);
	keyboard_keyclick_sound();
}

#define detect_mode_send_esc_sequence() \
	uart_send_escape(); \
	uart_send(parm_setting.bits.DECANM ? \
					(parm_setting.bits.DECCKM ? 'O' : '[') : '?' )
	
#define keypad_DECKPAM_alt_seq(alt, ch) \
	if(parm_setting.bits.DECKPAM) \
	{ \
		detect_mode_send_esc_sequence(); \
		uart_send('m'); \
	} \
	else \
	{ \
		uart_send('-'); \
	} \
	 \
	keyboard_keyclick_sound()

void keyboard_keypad_comma(void)
{
	keypad_DECKPAM_alt_seq('l', ',');
}
	
void keyboard_keypad_dash(void)
{
	keypad_DECKPAM_alt_seq('m', '-');
}

void keyboard_keypad_dot()
{	
	keypad_DECKPAM_alt_seq('n', '.');
}

void keyboard_pfn(kbdpfn_t pfn)
{
	detect_mode_send_esc_sequence();
	uart_send('p' + pfn);
}

void keyboard_keypad_enter(void)
{
	if(parm_setting.bits.DECKPAM)
	{
		/* keypad enter */
		detect_mode_send_esc_sequence();
		uart_send('M');
	}
	else
	{
		uart_send_enter();
	}
	
	keyboard_keyclick_sound();
}

void keyboard_keypad_num(const uint8_t num)
{
	const static uint8_t map[10] = 
	{
		'y', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x'
	};
	
	/* send according to Keypad mode */
	if(parm_setting.bits.DECKPAM)
	{
		detect_mode_send_esc_sequence();
		uart_send(map[num]);
	}
	else
	{
		/* send simple ascii code */
		uart_send('0' + num);
	}
	
	keyboard_keyclick_sound();
}

void keyboard_delete(void)
{
	uart_send(ASCII_DEL);
	keyboard_keyclick_sound();
}

void keyboard_return(void)
{
	uart_send_enter();
	keyboard_keyclick_sound();
}

void keyboard_setup(void)
{
	setup();
	keyboard_keyclick_sound();
}
