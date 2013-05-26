#include <keyboard/ps2.h>

struct __keyboard_ps2 keyboard_ps2 = 
{
	.index = -2,
};

void keyboard_ps2_data_decode()
{
	switch(keyboard_ps2.data)
	{
		case 0xF0:
			/* some key released */
			keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_MAKE;
		return;
		
		case 0xE0:
			/* behaviour modifier */
			keyboard_ps2.mode |= KEYBOARD_PS2_MODE_MODIFIER;
		return;
		
		case 0x12: /* left SHIFT */
		case 0x59: /* right SHIFT */
			if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_MAKE)
			{
				keyboard_ps2.mode |= KEYBOARD_PS2_MODE_LATCH_SHIFT;
			}
			else
			{
				keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_LATCH_SHIFT;
			}
		break;
		
		/* right CTRL : <modifier> 0x14 */
		case 0x14: /* left CTRL */
			if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_MAKE)
			{
				keyboard_ps2.mode |= KEYBOARD_PS2_MODE_LATCH_CTRL;
			}
			else
			{
				keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_LATCH_CTRL;
			}
		break;
		
		/* right ALT : <modifier> 0x11 */
		case 0x11: /* left ALT */
			if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_MAKE)
			{
				keyboard_ps2.mode |= KEYBOARD_PS2_MODE_LATCH_ALT;
			}
			else
			{
				keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_LATCH_ALT;
			}
		break;
		
		/* including modifier version */
		case 0x1F: /* left GUI */
			
		break;
		
		/* caps */
		case 0x58:
			if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_MAKE)
			{
				/* flip caps */
				keyboard_ps2.mode ^= KEYBOARD_PS2_MODE_LATCH_CAPS;
			}
		break;
		
		default:
			if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_MAKE)
			{
				keyboard_ps2_resolve_scancode(keyboard_ps2.data);
			}
		break;
	}
	
	keyboard_ps2.mode |= KEYBOARD_PS2_MODE_MAKE;
	keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_MODIFIER;
}

void keyboard_ps2_resolve_scancode()
{
	register uint8_t ch = 0;
	
	if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_MODIFIER)
	{
		switch (keyboard_ps2.data)
		{
			case 0x4A:
				ch = '/';
			break;
			
			case 0x5A:
				ch = KEYBOARD_PS2_ENTER;
			break;
			
			case 0x69:
				ch = KEYBOARD_PS2_END;
			break;
			
			case 0x6B:
				ch = KEYBOARD_PS2_LEFTARROW;
			break;
			
			case 0x6C:
				ch = KEYBOARD_PS2_HOME;
			break;
			
			case 0x70:
				ch = KEYBOARD_PS2_INSERT;
			break;
			
			case 0x71:
				ch = KEYBOARD_PS2_DELETE;
			break;
			
			case 0x72:
				ch = KEYBOARD_PS2_DOWNARROW;
			break;
			
			case 0x74:
				ch = KEYBOARD_PS2_RIGHTARROW;
			break;
			
			case 0x75:
				ch = KEYBOARD_PS2_UPARROW;
			break;
			
			case 0x7A:
				ch = KEYBOARD_PS2_PAGEDOWN;
			break;
			
			case 0x7D:
				ch = KEYBOARD_PS2_PAGEUP;
			break;
		}
	}
	else if(keyboard_ps2.data < KEYBOARD_PS2_KEYMAP_SIZE)
	{
		ch = keyboard_ps2_scancode_en[keyboard_ps2.data][ (keyboard_ps2.mode & KEYBOARD_PS2_MODE_LATCH_SHIFT) ? 1 : 0 ];
		
		if('a' <= ch && ch <= 'z')
		{
			/* we have small letters (ctrl or caps latched)*/
			if(keyboard_ps2.mode & (KEYBOARD_PS2_MODE_LATCH_CTRL | KEYBOARD_PS2_MODE_LATCH_CAPS))
			{
				/* convert to capital letter */
				ch -= 'a' - 'A';
			}
		}
		else if('A' <= ch && ch <= 'Z')
		{
			/* we have capital letters (ctrl not latched && caps latched)*/
			if(keyboard_ps2.mode & (KEYBOARD_PS2_MODE_LATCH_CTRL | KEYBOARD_PS2_MODE_LATCH_CAPS) == KEYBOARD_PS2_MODE_LATCH_CAPS)
			{
				/* convert to small letter */
				ch += 'a' - 'A';
			}
		}
		/* some other char */
		else if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_LATCH_CTRL)
		{
			/* cannot handle this condition currently */
			return;
		}
		
		if(keyboard_ps2.mode & KEYBOARD_PS2_MODE_LATCH_CTRL)
		{
			ch = (ch - '@') & ~BIT7;
		}
	}
	
	if(ch)
	{
		uart_send(ch);
	}
}
