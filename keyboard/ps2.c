#include <keyboard/ps2.h>

struct __keyboard_ps2 keyboard_ps2;

void keyboard_ps2_init()
{
	KEYBOARD_PS2_PDIR &= ~(KEYBOARD_PS2_DATA | KEYBOARD_PS2_CLK);
	KEYBOARD_PS2_PREN |= KEYBOARD_PS2_DATA | KEYBOARD_PS2_CLK;
	KEYBOARD_PS2_POUT |= KEYBOARD_PS2_DATA | KEYBOARD_PS2_CLK;
	
	KEYBOARD_PS2_PIES |= KEYBOARD_PS2_CLK;
	KEYBOARD_PS2_PIE |= KEYBOARD_PS2_CLK;
	
	KEYBOARD_PS2_PIFG &= ~KEYBOARD_PS2_CLK;
	
	P1DIR |= BIT6;
	P1OUT &= ~BIT6;
	
	keyboard_ps2.index = -2;
	
	/* interrupt goes to pin1_interrupt() */
}

void keyboard_ps2_data_decode()
{
	if(keyboard_ps2.modifier)
	{
		/* before recv this data , we got MODIFIER */
		switch(keyboard_ps2.data)
		{
			case 0x14: /* right CTRL */
				keyboard_ps2.latch_ctrl = keyboard_ps2._break;
			break;
			
			case 0x11: /* right ALT */
				keyboard_ps2.latch_alt = keyboard_ps2._break;
			break;
			
			case 0x1F: /* right GUI */
				keyboard_ps2.latch_gui = keyboard_ps2._break;
			break;
			
			//default:
				//ignore
		}
	}
	else
	{
		switch(keyboard_ps2.data)
		{
			case 0xF0:
				/* _break == KEY RELEASE */
				keyboard_ps2._break = TRUE;
				return;
			break;
			
			case 0xE0:
				/* behaviour modifier */
				keyboard_ps2.modifier = TRUE;
				return;
			break;
			
			case 0x12: /* left SHIFT */
			case 0x59: /* right SHIFT */
				keyboard_ps2.latch_shift = keyboard_ps2._break;
			break;
			
			case 0x14: /* left CTRL */
				keyboard_ps2.latch_ctrl = keyboard_ps2._break;
			break;
			
			case 0x11: /* left ALT */
				keyboard_ps2.latch_alt = keyboard_ps2._break;
			break;
			
			case 0x1F: /* left GUI */
				keyboard_ps2.latch_gui = keyboard_ps2._break;
			break;
			
			default:
				keyboard_ps2_resolve_scancode();
		}
	}
	
	keyboard_ps2._break = FALSE;
	keyboard_ps2.modifier = FALSE;
}

void keyboard_ps2_resolve_scancode()
{
	register uint8_t ch = 0;
	
	if(keyboard_ps2.modifier)
	{
		switch (keyboard_ps2.data)
		{
			case 0x70:
				ch = KEYBOARD_PS2_INSERT;
			break;
			
			case 0x6C:
				ch = KEYBOARD_PS2_HOME;
			break;
			
			case 0x7D:
				ch = KEYBOARD_PS2_PAGEUP;
			break;
		  
			case 0x71:
				ch = KEYBOARD_PS2_DELETE;
			break;
		  
			case 0x69:
				ch = KEYBOARD_PS2_END;
			break;
		  
			case 0x7A:
				ch = KEYBOARD_PS2_PAGEDOWN;
			break;
		  
			case 0x75:
				ch = KEYBOARD_PS2_UPARROW;
			break;
		  
			case 0x6B:
				ch = KEYBOARD_PS2_LEFTARROW;
			break;
		  
			case 0x72:
				ch = KEYBOARD_PS2_DOWNARROW;
			break;
		  
			case 0x74:
				ch = KEYBOARD_PS2_RIGHTARROW;
			break;
		  
			case 0x4A:
				ch = '/';
			break;
		  
			case 0x5A:
				ch = KEYBOARD_PS2_ENTER;
			break;
		}
	}
	else if(keyboard_ps2.data < KEYBOARD_PS2_KEYMAP_SIZE)
	{
		if(keyboard_ps2.latch_shift)
		{
			ch = keyboard_ps2_scancode_en[keyboard_ps2.data][0];
		}
		else
		{
			ch = keyboard_ps2_scancode_en[keyboard_ps2.data][1];
		}
	}
	
	if(ch)
	{
		cqueue_push(&uart_cqueue_rx, ch);
	}
}

void port2_interrupt()
{
	P1OUT ^= BIT6;
	
	KEYBOARD_PS2_PIFG &= ~KEYBOARD_PS2_CLK;
	keyboard_ps2.index++;
	
	switch(keyboard_ps2.index)
	{
		case -1:
			keyboard_ps2.data = 0;
			/* start bit */
		break;
		
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			/* data */
			if(KEYBOARD_PS2_PIN & KEYBOARD_PS2_DATA)
			{
				keyboard_ps2.data |= (1 << keyboard_ps2.index);
			}
		break;
		
		case 8:
			/* TODO: check parity for data */
		break;
		
		case 9:
			/* STOP bit */
			keyboard_ps2_data_decode();
		default:
			/* reset */
			keyboard_ps2.index = -2;
		break;
	}
}
