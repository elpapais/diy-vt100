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
			keyboard_ps2.make = FALSE;
		return;
		
		case 0xE0:
			/* behaviour modifier */
			keyboard_ps2.modifier = TRUE;
		return;
		
		case 0x12: /* left SHIFT */
		case 0x59: /* right SHIFT */
			keyboard_ps2.latch_shift = keyboard_ps2.make;
		break;
		
		/* right CTRL : <modifier> 0x14 */
		case 0x14: /* left CTRL */
			keyboard_ps2.latch_ctrl = keyboard_ps2.make;
		break;
		
		/* right ALT : <modifier> 0x11 */
		case 0x11: /* left ALT */
			keyboard_ps2.latch_alt = keyboard_ps2.make;
		break;
		
		/* including modifier version */
		case 0x1F: /* left GUI */
			//keyboard_ps2.latch_gui = keyboard_ps2.make;
		break;
		
		/* caps */
		case 0x58:
			if(keyboard_ps2.make)
			{
				/* flip caps */
				keyboard_ps2.latch_caps ^= 0x01;
			}
		break;
		
		default:
			if(keyboard_ps2.make)
			{
				return keyboard_ps2_resolve_scancode(keyboard_ps2.data);
			}
		break;
	}
	
	keyboard_ps2.make = TRUE;
	keyboard_ps2.modifier = FALSE;
}

void keyboard_ps2_resolve_scancode()
{
	register uint8_t ch = 0;
	
	if(keyboard_ps2.modifier)
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
		ch = keyboard_ps2_scancode_en[keyboard_ps2.data][keyboard_ps2.latch_shift];
		
		/* caps lock feature, turn character to opposite case */
		if(keyboard_ps2.latch_caps)
		{
			if('a' <= ch && ch <= 'z' )
			{
				ch -= 'a' - 'A';
			}
			else if('A' <= ch && ch <= 'Z')
			{
				ch += 'a' - 'A';
			}
		}
	}
	
	if(ch)
	{
		uart_send(ch);
		//cqueue_push(&uart_cqueue_rx, ch);
	}
}
