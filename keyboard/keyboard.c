#include <diy-vt100/keyboard/keyboard.h>
#include <diy-vt100/keyboard/scancode.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/bell.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/vt100/misc.h>
#include <diy-vt100/setup.h>

kbd_t kbd;

#define break_event_stop()  \
	if(kbd.latch._break) \
	{ \
		return; \
	}
	
#define keyclick_sound() \
	if(parm_setting.bits.KEYCLICK) \
	{ \
		bell_short(); \
	}

#define kbd_fn(ident) \
	break_event_stop(); \
	uart_send_escape(); \
	uart_send(parm_setting.bits.DECANM ? 'O' : '?');\
	uart_send(ident); \
	keyclick_sound()

#define kbd_keypad(ascii, appmode, arrow) \
	break_event_stop(); \
	 \
	/* arrow key pressed */ \
	if(kbd.latch.modifier) \
	{ \
		if(arrow) \
		{ \
			kbd_arrow(arrow); \
		} \
	} \
	/* send accoring to Keypad mode */ \
	else if(parm_setting.bits.DECKPAM) \
	{ \
		uart_send_escape(); \
		uart_send(parm_setting.bits.DECANM ? 'O' : '?'); \
		uart_send(appmode); \
	} \
	else \
	{ \
		/* send simple ascii code */ \
		uart_send(ascii); \
	} \
	 \
	keyclick_sound()

#define kbd_arrow(ident) \
	uart_send_escape(); \
	 \
	if(parm_setting.bits.DECANM) \
	{ \
		uart_send(parm_setting.bits.DECCKM ? 'O' : '['); \
	} \
	 \
	uart_send(ident); \
	keyclick_sound()

void kbd_decode()
{
	register uint8_t ch = 0;
	
	if(kbd.param < KBD_SCANCODE_SIZE)
	{
		switch((uint16_t)kbd_scancode[kbd.param].callback)
		{
			/* only caps is latched */
			case 1:
				if(kbd.latch.caps && ! kbd.latch.ctrl)
				{
					ch = 1;
				}
							
			case 0:
				if(kbd.latch._break)
				{
					break;
				}
				
				if(kbd.latch.shift || kbd.latch.ctrl)
				{
					ch ^= 1;
				}
				
				ch = kbd_scancode[kbd.param].ch[ch];
				
				if(kbd.latch.ctrl)
				{
					ch -= '@';
					__low(ch, BIT7);
				}
				
				uart_send(ch);
				
				keyclick_sound();
			break;
			
			default:
				kbd_scancode[kbd.param].callback();
			break;
		}
		
		kbd.latch._break = FALSE;
		kbd.latch.modifier = FALSE;
	}
	else
	{
		switch(kbd.param)
		{
			case 0xF0:
				/* some key released */
				kbd.latch._break = TRUE;
			break;
			
			case 0xE0:
				kbd.latch.modifier = TRUE;
			break;
		}
	}
}

void kbd_f1()
{
	kbd_fn('P');
}
void kbd_f2()
{
	kbd_fn('Q');
}
void kbd_f3()
{
	kbd_fn('R');
}
void kbd_f4()
{
	kbd_fn('S');
}

void kbd_f5()
{
	break_event_stop();
	setup();
}

void kbd_caps()
{
	/* caps status modify */
	if(! kbd.latch._break)
	{
		kbd.latch.caps ^= TRUE;
		keyclick_sound();
	}
}

void kbd_shift()
{
	kbd.latch.shift = kbd.latch._break ? FALSE : TRUE;
}
		
void kbd_ctrl()
{
	kbd.latch.ctrl = kbd.latch._break ? FALSE : TRUE;
}

void kbd_keypad_0()
{
	kbd_keypad('0', 'p', 0);
}
void kbd_keypad_1()
{
	kbd_keypad('1', 'q', 0);
}
void kbd_keypad_2()
{
	kbd_keypad('2', 'r', 'B');
}
void kbd_keypad_3()
{
	kbd_keypad('3', 's', 0);
}
void kbd_keypad_4()
{
	kbd_keypad('4', 't', 'D');
}
void kbd_keypad_5()
{
	kbd_keypad('5', 'u', 0);
}
void kbd_keypad_6()
{
	kbd_keypad('6', 'v', 'C');
}
void kbd_keypad_7()
{
	kbd_keypad('7', 'w', 0);
}
void kbd_keypad_8()
{
	kbd_keypad('2', 'x', 'A');
}
void kbd_keypad_9()
{
	kbd_keypad('9', 'y', 0);
}
void kbd_keypad_dash()
{
	kbd_keypad('-', 'm', 0);
}

void
kbd_keypad_dot()
{
	/* below code is a modified version of *keypad()
	 * any future update to it , are also carried here too */
	 
	 break_event_stop();
	
	/* arrow key pressed */
	if(kbd.latch.modifier)
	{
		uart_send(ASCII_DEL);
	}
	/* send accoring to Keypad mode */
	else if(setting.bits.DECKPAM)
	{
		uart_send_escape();
		uart_send(setting.bits.DECANM ? 'O' : '?');
		/* appmode = 'n' */
		uart_send('n');
	}
	else
	{
		/* send simple ascii code (ascii = '.') */
		uart_send('.');
	}
	
	keyclick_sound();
}

void
kbd_enter()
{
	break_event_stop();
	
	if(kbd.latch.modifier && setting.bits.DECKPAM)
	{
		/* keypad enter */
		uart_send_escape();
		uart_send(setting.bits.DECANM ? 'O' : '?');
		uart_send('M');
	}
	else
	{
		uart_send_enter();
	}
	
	keyclick_sound();
}

void kbd_break()
{
	
}
