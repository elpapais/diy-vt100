#include <keyboard/ps2.h>
#include <uart.h>
#include <vt100/misc.h>
#include <setup.h>
#include <setting.h>

struct __keyboard_ps2 keyboard_ps2;

static inline void keyboard_ps2_scancode_arrow(const uint8_t cursor);
static inline void keyboard_ps2_scancode_keypad(const uint8_t ascii, const uint8_t appmode, const uint8_t cursor);

void
keyboard_ps2_data_decode()
{
	uint8_t ch = 0;
	
	if(keyboard_ps2.param < KEYBOARD_PS2_SCANCODE_SIZE)
	{
		switch((uint16_t)keyboard_ps2_scancode_en[keyboard_ps2.param].callback)
		{
			case 1:
				if(keyboard_ps2.mode & (KEYBOARD_PS2_MODE_LATCH_CTRL | 
										KEYBOARD_PS2_MODE_LATCH_CAPS) 
					== KEYBOARD_PS2_MODE_LATCH_CAPS)
				{
					ch = 1;
				}
			
			case 0:
				if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK)
				{
					break;
				}
				
				if(keyboard_ps2.mode & (KEYBOARD_PS2_MODE_LATCH_CTRL
										| KEYBOARD_PS2_MODE_LATCH_SHIFT))
				{
					ch ^= 1;
				}
				
				ch = keyboard_ps2_scancode_en[keyboard_ps2.param].ch[ch];
				
				if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_LATCH_CTRL)
				{
					ch = (ch - '@') & ~BIT7;
				}
				
				uart_send(ch);
			break;
			
			default:
				keyboard_ps2_scancode_en[keyboard_ps2.param].callback();
			break;
		}
		
		keyboard_ps2.mode &= ~(KEYBOARD_PS2_MODE_BREAK 
								| KEYBOARD_PS2_MODE_MODIFIER);
	}
	else
	{
		switch(keyboard_ps2.param)
		{
			case 0xF0:
				/* some key released */
				keyboard_ps2.mode |= KEYBOARD_PS2_MODE_BREAK;
			break;
			
			case 0xE0:
				keyboard_ps2.mode |= KEYBOARD_PS2_MODE_MODIFIER;
			break;
		}
	}
}

static void
keyboard_ps2_scancode_fn(const uint8_t ident)
{
	uart_send_escape();

	if(setting_read(SETTING_DECANM))
	{
		uart_send('O');
	}
	
	uart_send(ident);
}

void
keyboard_ps2_scancode_callback_f1()
{
	keyboard_ps2_scancode_fn('P');
}

void
keyboard_ps2_scancode_callback_f2()
{
	keyboard_ps2_scancode_fn('Q');
}

void
keyboard_ps2_scancode_callback_f3()
{
	keyboard_ps2_scancode_fn('R');
}

void
keyboard_ps2_scancode_callback_f4()
{
	keyboard_ps2_scancode_fn('S');
}

void
keyboard_ps2_scancode_callback_f5()
{
	if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK)
	{
		return;
	}
	
	setup();
}

void
keyboard_ps2_scancode_callback_caps()
{
	/* caps status modify */
	if(!(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK))
	{
		/* flip caps */
		keyboard_ps2.mode ^= KEYBOARD_PS2_MODE_LATCH_CAPS;
	}
}

void
keyboard_ps2_scancode_callback_shift()
{
	/* shift status modify */
	if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK)
	{
		keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_LATCH_SHIFT;
	}
	else
	{
		keyboard_ps2.mode |= KEYBOARD_PS2_MODE_LATCH_SHIFT;
	}
}

void
keyboard_ps2_scancode_callback_ctrl()
{
	/* ctrl status modify */
	if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK)
	{
		keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_LATCH_CTRL;
	}
	else
	{
		keyboard_ps2.mode |= KEYBOARD_PS2_MODE_LATCH_CTRL;
	}
}

void
keyboard_ps2_scancode_callback_keypad_0()
{
	keyboard_ps2_scancode_keypad('0', 'p', 0);
}

void
keyboard_ps2_scancode_callback_keypad_1()
{
	keyboard_ps2_scancode_keypad('1', 'q', 0);
}

void
keyboard_ps2_scancode_callback_keypad_2()
{
	keyboard_ps2_scancode_keypad('2', 'r', 'B');
}

void
keyboard_ps2_scancode_callback_keypad_3()
{
	keyboard_ps2_scancode_keypad('3', 's', 0);
}

void
keyboard_ps2_scancode_callback_keypad_4()
{
	keyboard_ps2_scancode_keypad('4', 't', 'D');
}

void
keyboard_ps2_scancode_callback_keypad_5()
{
	keyboard_ps2_scancode_keypad('5', 'u', 0);
}

void
keyboard_ps2_scancode_callback_keypad_6()
{
	keyboard_ps2_scancode_keypad('6', 'v', 'C');
}

void
keyboard_ps2_scancode_callback_keypad_7()
{
	keyboard_ps2_scancode_keypad('7', 'w', 0);
}

void
keyboard_ps2_scancode_callback_keypad_8()
{
	keyboard_ps2_scancode_keypad('2', 'x', 'A');
}

void
keyboard_ps2_scancode_callback_keypad_9()
{
	keyboard_ps2_scancode_keypad('9', 'y', 0);
}

void
keyboard_ps2_scancode_callback_keypad_dot()
{
	/* below code is a modified version of *keypad()
	 * any future update to it , are also carried here too */
	 
	 if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK)
	{
		return;
	}
	
	/* arrow key pressed */
	if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_MODIFIER)
	{
		uart_send(ASCII_DEL);
	}
	/* send accoring to Keypad mode */
	else if(setting_read(SETTING_DECKPAM))
	{
		uart_send_escape();
		uart_send(setting_read(SETTING_DECANM) ? 'O' : '?');
		/* appmode = 'n' */
		uart_send('n');
	}
	else
	{
		/* send simple ascii code (ascii = '.') */
		uart_send('.');
	}
}

void
keyboard_ps2_scancode_callback_keypad_dash()
{
	keyboard_ps2_scancode_keypad('-', 'm', 0);
}

void
keyboard_ps2_scancode_callback_enter()
{
	if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK)
	{
		return;
	}
	
	if(
		keyboard_ps2.mode & KEYBOARD_PS2_MODE_MODIFIER
		&& setting_read(SETTING_DECKPAM)
	)
	{
		/* keypad enter */
		uart_send_escape();
		uart_send(setting_read(SETTING_DECANM) ? 'O' : '?');
		uart_send('M');
	}
	else
	{
		uart_send_enter();
	}
}

static inline void
keyboard_ps2_scancode_keypad(const uint8_t ascii, const uint8_t appmode,
							const uint8_t arrow)
{
	if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK)
	{
		return;
	}
	
	/* arrow key pressed */
	if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_MODIFIER)
	{
		if(arrow)
		{
			keyboard_ps2_scancode_arrow(arrow);
		}
	}
	/* send accoring to Keypad mode */
	else if(setting_read(SETTING_DECKPAM))
	{
		uart_send_escape();
		uart_send(setting_read(SETTING_DECANM) ? 'O' : '?');
		uart_send(appmode);
	}
	else
	{
		/* send simple ascii code */
		uart_send(ascii);
	}
}

static inline void
keyboard_ps2_scancode_arrow(const uint8_t ident)
{
	uart_send_escape();
	
	/* are in ANSI Mode ? */
	if(setting_read(SETTING_DECANM))
	{
		uart_send( setting_read(SETTING_DECCKM) ? 'O' : '[');
	}
	
	uart_send(ident);
}
