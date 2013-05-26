#include <keyboard/ps2.h>

struct __keyboard_ps2 keyboard_ps2;

void
keyboard_ps2_data_decode()
{
	register uint8_t ch = 0;
	
	if(keyboard_ps2.data < KEYBOARD_PS2_KEYMAP_SIZE)
	{
		switch((uint16_t)keyboard_ps2_scancode_en[keyboard_ps2.data].callback)
		{
			case 1:
				if(keyboard_ps2.mode & (KEYBOARD_PS2_MODE_LATCH_CTRL | KEYBOARD_PS2_MODE_LATCH_CAPS) == KEYBOARD_PS2_MODE_LATCH_CAPS)
				{
					ch = 1;
				}
			
			case 0:
				if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK)
				{
					break;
				}
				
				if(keyboard_ps2.mode & (KEYBOARD_PS2_MODE_LATCH_CTRL | KEYBOARD_PS2_MODE_LATCH_SHIFT))
				{
					ch ^= 1;
				}
				
				ch = keyboard_ps2_scancode_en[keyboard_ps2.data].ch[ch];
				
				if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_LATCH_CTRL)
				{
					ch = (ch - '@') & ~BIT7;
				}
				
				uart_send(ch);
			break;
			
			default:
				keyboard_ps2_scancode_en[keyboard_ps2.data].callback();
			break;
		}
		
		keyboard_ps2.mode &= ~(KEYBOARD_PS2_MODE_BREAK | KEYBOARD_PS2_MODE_MODIFIER);
	}
	else
	{
		switch(keyboard_ps2.data)
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

#define keyboard_ps2_scancode_callback_f(inc) \
	vt100_param.count = 3; \
	vt100_param.data[0] = ASCII_ESCAPE; \
	vt100_param.data[1] = 'O'; \
	vt100_param.data[2] = 'O' + inc; \
	uart_send_param_direct()

void
keyboard_ps2_scancode_callback_f1()
{
	keyboard_ps2_scancode_callback_f(1);
}

void
keyboard_ps2_scancode_callback_f2()
{
	keyboard_ps2_scancode_callback_f(2);
}

void
keyboard_ps2_scancode_callback_f3()
{
	keyboard_ps2_scancode_callback_f(3);
}

void
keyboard_ps2_scancode_callback_f4()
{
	keyboard_ps2_scancode_callback_f(4);
}

void
keyboard_ps2_scancode_callback_alt()
{
	if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK)
	{
		keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_LATCH_ALT;
	}
	else
	{
		keyboard_ps2.mode |= KEYBOARD_PS2_MODE_LATCH_ALT;
	}
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
keyboard_ps2_scancode_callback_numlock()
{
	/* numlock status modify */
	if(!(keyboard_ps2.mode & KEYBOARD_PS2_MODE_BREAK))
	{
		/* flip numlock */
		keyboard_ps2.mode ^= KEYBOARD_PS2_MODE_LATCH_NUM;
	}
}
