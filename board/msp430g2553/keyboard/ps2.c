#include <diy-vt100/setting.h>
#include <diy-vt100/bell.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/setup.h>

/* ===  */
/*
void ps2kbd_ctrl(void);
void ps2kbd_shift(void);
void ps2kbd_caps(void);
void ps2kbd_f5(void);
void ps2kbd_f4(void);
void ps2kbd_f3(void);
void ps2kbd_f2(void);
void ps2kbd_f1(void);
void ps2kbd_enter(void);
void ps2kbd_space(void)
void ps2kbd_tab(void);
void ps2kbd_escape(void);
void ps2kbd_backspace(void);

void ps2kbd_keypad_0(void);
void ps2kbd_keypad_1(void);
void ps2kbd_keypad_2(void);
void ps2kbd_keypad_3(void);
void ps2kbd_keypad_4(void);
void ps2kbd_keypad_5(void);
void ps2kbd_keypad_6(void);
void ps2kbd_keypad_7(void);
void ps2kbd_keypad_8(void);
void ps2kbd_keypad_9(void);
void ps2kbd_keypad_dot(void);
void ps2kbd_keypad_dash(void);
*/
#define PS2KBD_SCANCODE_SIZE 126

typedef struct
{
	/*
	 * 0 = do not exists
	 * 1 = character is affected by caps status
	 * other = call
	 */
	callback_t callback;

	/* 0:main, 1:replacement */
	uint8_t ch[2];
}
ps2kbdscancode_t;

inline void keyclick_sound(void)
{
	if(parm_setting.bits.KEYCLICK)
	{
		bell_short();
	}
}

extern const ps2kbdscancode_t ps2kbd_scancode[PS2KBD_SCANCODE_SIZE];

#define KBD_MODIFIER HW_PRIV1
#define KBD_BREAK HW_PRIV2

/* === */

inline void ps2kbd_other_setup(const uint8_t ch);

void ps2kbd_decode(const uint8_t data)
{
	if(data < PS2KBD_SCANCODE_SIZE)
	{
		const ps2kbdscancode_t *scancode = &ps2kbd_scancode[data];

		if(scancode->callback > (callback_t)2)
		{
			if(! setting.bits.KBD_BREAK || scancode->ch[0])
			{
				/* continue if break is reset or explicitly required */
				scancode->callback();
			}
		}
		else if(scancode->callback)
		{
			if(! setting.bits.KBD_BREAK)
			{
				if(setting.bits.SETUP_SHOW)
				{
					ps2kbd_other_setup(scancode->ch[0]);
				}
				else if(setting.bits.KBD_CTRL)
				{
					register uint8_t ch = scancode->ch[1];

					switch(ch)
					{
						case '{':
							ch = '[';
						break;
						
						case '|':
							ch = '\\';
						break;
						
						case '}':
							ch = ']';
						break;
					}

					if(ch >= '@' && ch <= '_')
					{
						uart_send(ch - '@');
						keyclick_sound();
					}
				}
				else
				{
					register uint8_t ch = 0;

					/* caps affected */
					if(scancode->callback == (callback_t)1 
						&& setting.bits.KBD_CAPS)
					{
						ch |= 1;
					}

					if(setting.bits.KBD_SHIFT)
					{
						ch ^= 1;
					}

					uart_send(scancode->ch[ch]);
					keyclick_sound();

				}
			}
		}

		setting.bits.KBD_BREAK = FALSE;
		setting.bits.KBD_MODIFIER = FALSE;
	}
	else
	{
		switch(data)
		{
			case 0xF0:
				/* some key released */
				setting.bits.KBD_BREAK = TRUE;
			break;

			case 0xE0:
				setting.bits.KBD_MODIFIER = TRUE;
			break;
		}
	}
}

inline void ps2kbd_other_setup(const uint8_t ch)
{
	switch(ch)
	{
		case '0':
			setup_reset();
		break;

		case '2':
			setup_TAB_flip();
		break;

		case '3':
			setup_TABS_clear();
		break;

		case '4':
			setup_LOCAL();
		break;

		case '5':
			setup_switch();
		break;

		case '6':
			setup_value_flip();
		break;

		case '7':
			setup_uart_tx();
		break;

		case '8':
			setup_uart_rx();
		break;

		case '9':
			setup_DECCOLM();
		break;

		case ' ':
			setup_next_setting();
		break;

		case 's':
			if(setting.bits.KBD_SHIFT)
			{
				setup_save();
			}
			else
			{
				return;
			}
		break;

		case 'r':
			if(setting.bits.KBD_SHIFT)
			{
				setup_recall();
			}
			else
			{
				return;
			}
		break;

		default:
			return;
		break;
	}

	keyclick_sound();
}

void ps2kbd_f1(void)
{
	uart_send_keypad_pfn(PF1);
	keyclick_sound();
}

void ps2kbd_f2(void)
{
	uart_send_keypad_pfn(PF2);
	keyclick_sound();
}

void ps2kbd_f3(void)
{
	uart_send_keypad_pfn(PF3);
	keyclick_sound();
}

void ps2kbd_f4(void)
{
	uart_send_keypad_pfn(PF4);
	keyclick_sound();
}

/* working as SETUP key */
void ps2kbd_f5(void)
{
	setup();
	keyclick_sound();
}

void ps2kbd_caps(void)
{
	/* caps status modify */
	if(! setting.bits.KBD_BREAK)
	{
		setting.bits.KBD_CAPS ^= TRUE;
		keyclick_sound();
	}
}

void ps2kbd_shift(void)
{
	setting.bits.KBD_SHIFT = setting.bits.KBD_BREAK ? FALSE : TRUE;
}

void ps2kbd_ctrl(void)
{
	setting.bits.KBD_CTRL = setting.bits.KBD_BREAK ? FALSE : TRUE;
}

void __ps2kbd_mux_keypad_num_arrow(const uint8_t num, const uint8_t arrow)
{
	if(setting.bits.KBD_MODIFIER)
	{
		/* arrow key pressed */
		uart_send_arrow(arrow);
	}
	else
	{
		/* send accoring to Keypad mode */
		uart_send_keypad_num(num);
	}
}

void ps2kbd_keypad_0(void)
{
	uart_send_keypad_num(0);
	keyclick_sound();
}

void ps2kbd_keypad_1(void)
{
	uart_send_keypad_num(1);
	keyclick_sound();
}

void ps2kbd_keypad_2(void)
{
	if(setting.bits.SETUP_SHOW)
	{
		setup_brightness_decrease();
	}
	else
	{
		__ps2kbd_mux_keypad_num_arrow(2, DOWN);
	}
	keyclick_sound();
}

void ps2kbd_keypad_3(void)
{
	uart_send_keypad_num(3);
}

void ps2kbd_keypad_4(void)
{
	if(setting.bits.SETUP_SHOW)
	{
		setup_previous_setting();
	}
	else
	{
		__ps2kbd_mux_keypad_num_arrow(4, LEFT);
	}
	keyclick_sound();
}

void ps2kbd_keypad_5(void)
{
	uart_send_keypad_num(5);
	keyclick_sound();
}

void ps2kbd_keypad_6(void)
{
	if(setting.bits.SETUP_SHOW)
	{
		setup_next_setting();
	}
	else
	{
		__ps2kbd_mux_keypad_num_arrow(6, RIGHT);
	}
	
	keyclick_sound();
}

void ps2kbd_keypad_7(void)
{
	uart_send_keypad_num(7);
	keyclick_sound();
}

void ps2kbd_keypad_8(void)
{
	if(setting.bits.SETUP_SHOW)
	{
		setup_brightness_increase();
	}
	else
	{
		__ps2kbd_mux_keypad_num_arrow(8, UP);
	}
	
	keyclick_sound();
}

void ps2kbd_keypad_9(void)
{
	uart_send_keypad_num(9);
	keyclick_sound();
}

void ps2kbd_keypad_dash(void)
{
	if(! setting.bits.SETUP_SHOW)
	{
		uart_send_keypad_dash();
		keyclick_sound();
	}
}

void
ps2kbd_keypad_dot(void)
{
	if(setting.bits.KBD_MODIFIER)
	{
		uart_send(ASCII_DEL);
	}
	else
	{
		uart_send_keypad_dot();
	}

	keyclick_sound();
}

void
ps2kbd_enter(void)
{
	if(setting.bits.SETUP_SHOW)
	{
		if(! setting.bits.KBD_MODIFIER)
		{
			setup_next_setting();
		}
		else
		{
			return;
		}
	}
	else
	{
		if(setting.bits.KBD_MODIFIER)
		{
			uart_send_keypad_enter();
		}
		else
		{
			uart_send_return();
		}
	}

	keyclick_sound();
}

void ps2kbd_break(void)
{

}

void ps2kbd_backspace(void)
{
	if(setting.bits.SETUP_SHOW)
	{
		setup_previous_setting();
	}
	else
	{
		uart_send(ASCII_BS);
	}

	keyclick_sound();
}

void ps2kbd_escape(void)
{
	if(! setting.bits.SETUP_SHOW)
	{
		uart_send(ASCII_ESCAPE);
		keyclick_sound();
	}
}

void ps2kbd_tab(void)
{
	if(setting.bits.SETUP_SHOW)
	{
		setup_next_setting();
	}
	else
	{
		uart_send(ASCII_TAB);
	}
	
	keyclick_sound();
}

void ps2kbd_space(void)
{
	if(setting.bits.SETUP_SHOW)
	{
		setup_next_setting();
	}
	else
	{
		uart_send(' ');
	}

	keyclick_sound();
}

/* === key mapping === */

#define number(ch, ch_alt) 	{(callback_t)2, {ch, ch_alt}}
#define special(ch, ch_alt) {(callback_t)2, {ch, ch_alt}}
#define alphabet(ch, ch_alt) {(callback_t)1, {ch, ch_alt}}
#define callback(cb) 		{cb}
#define ignore() 			{0}

/* require break */
#define callback_rb(cb) 	{cb, {1}}

const ps2kbdscancode_t ps2kbd_scancode[PS2KBD_SCANCODE_SIZE] =
{
	ignore	(),
	ignore	(), /* KEYBOARD_PS2_F9 */
	ignore	(),
	callback(ps2kbd_f5), /* KEYBOARD_PS2_F5 */
	callback(ps2kbd_f3),
	callback(ps2kbd_f1),
	callback(ps2kbd_f2),
	ignore	(), /* KEYBOARD_PS2_F12 */
	ignore	(),
	ignore	(), /* KEYBOARD_PS2_F10 */
	ignore	(), /* KEYBOARD_PS2_F8 */
	ignore	(), /* KEYBOARD_PS2_F6 */
	callback(ps2kbd_f4),
	callback(ps2kbd_tab),//special	(ASCII_TAB, ASCII_TAB),
	special	('`', '~'),
	ignore	(),
	ignore	(),
	ignore	(), /* left alt */
	callback_rb(ps2kbd_shift), /* left shift */
	ignore	(),
	callback_rb(ps2kbd_ctrl), /* left ctrl */
	alphabet('q', 'Q'),
	number	('1', '!'),
	ignore	(),
	ignore	(),
	ignore	(),
	alphabet('z', 'Z'),
	alphabet('s', 'S'),
	alphabet('a', 'A'),
	alphabet('w', 'W'),
	number	('2', '@'),
	ignore	(),
	ignore	(),
	alphabet('c', 'C'),
	alphabet('x', 'X'),
	alphabet('d', 'D'),
	alphabet('e', 'E'),
	number	('4', '$'),
	number	('3', '#'),
	ignore	(),
	ignore	(),
	alphabet(' ', ' '),
	alphabet('v', 'V'),
	alphabet('f', 'F'),
	alphabet('t', 'T'),
	alphabet('r', 'R'),
	number	('5', '%'),
	ignore	(),
	ignore	(),
	alphabet('n', 'N'),
	alphabet('b', 'B'),
	alphabet('h', 'H'),
	alphabet('g', 'G'),
	alphabet('y', 'Y'),
	number	('6', '^'),
	ignore	(),
	ignore	(),
	ignore	(),
	alphabet('m', 'M'),
	alphabet('j', 'J'),
	alphabet('u', 'U'),
	number	('7', '&'),
	number	('8', '*'),
	ignore	(),
	ignore	(),
	special	(',', '<'),
	alphabet('k', 'K'),
	alphabet('i', 'I'),
	alphabet('o', 'O'),
	number	('0', ')'),
	number	('9', '('),
	ignore	(),
	ignore	(),
	special	('.', '>'),
	special	('/', '?'),
	alphabet('l', 'L'),
	special	(';', ':'),
	alphabet('p', 'P'),
	special	('-', '_'),
	ignore	(),
	ignore	(),
	ignore	(),
	special	('\'', '"'),
	ignore	(),
	special	('[', '{'),
	special	('=', '+'),
	ignore	(),
	ignore	(),
	callback_rb(ps2kbd_caps),
	callback_rb(ps2kbd_shift), /* right shift */
	callback(ps2kbd_enter),
	special	(']', '}'),
	ignore	(),
	special	('\\', '|'),
	ignore	(),
	ignore	(),
	ignore	(),
	ignore	(),
	ignore	(),
	ignore	(),
	ignore	(),
	ignore	(),
	callback(ps2kbd_backspace),//special	(ASCII_BS, ASCII_BS),
	ignore	(),
	ignore	(),
	callback(ps2kbd_keypad_1),
	ignore	(),
	callback(ps2kbd_keypad_4),
	callback(ps2kbd_keypad_7),
	ignore	(),
	ignore	(),
	ignore	(),
	callback(ps2kbd_keypad_0),
	callback(ps2kbd_keypad_dot),
	callback(ps2kbd_keypad_2),
	callback(ps2kbd_keypad_5),
	callback(ps2kbd_keypad_6),
	callback(ps2kbd_keypad_8),
	callback(ps2kbd_escape),//special	(ASCII_ESCAPE, ASCII_ESCAPE),
	ignore	(), /* num lock */
	ignore	(), /* KEYBOARD_PS2_F11 */
	special	('+', '+'),
	callback(ps2kbd_keypad_3),
	callback(ps2kbd_keypad_dash),
	special	('*', '*'),
	callback(ps2kbd_keypad_9)
//	ignore(), /* KEYBOARD_PS2_SCROLL */
//	ignore(),
//	ignore(),
//	ignore(),
//	ignore(),
//	ignore(), /* KEYBOARD_PS2_F7 */
};


