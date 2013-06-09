#include <keyboard/keyboard.h>
#include <keyboard/scancode.h>
#include <hardware/flash.h>
#include <hardware/buzzer.h>
#include <uart.h>
#include <vt100/misc.h>
#include <setup.h>

struct __kbd kbd;

#define break_event_stop()  \
	if(kbd_latch_read(KBD_BREAK)) \
	{ \
		return; \
	}
	
#define keyclick_sound() \
	if(flash_setting_read(SETTING_KEYCLICK)) \
	{ \
		buzzer_short(); \
	}

#define kbd_fn(ident) \
	break_event_stop(); \
	uart_send_escape(); \
	if(flash_setting_read(SETTING_DECANM)) \
	{\
		uart_send('O');\
	}\
	uart_send(ident); \
	keyclick_sound()

#define kbd_keypad(ascii, appmode, arrow) \
	break_event_stop(); \
	 \
	/* arrow key pressed */ \
	if(kbd_latch_read(KBD_MODIFIER)) \
	{ \
		if(arrow) \
		{ \
			kbd_arrow(arrow); \
		} \
	} \
	/* send accoring to Keypad mode */ \
	else if(flash_setting_read(SETTING_DECKPAM)) \
	{ \
		uart_send_escape(); \
		uart_send(flash_setting_read(SETTING_DECANM) ? 'O' : '?'); \
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
	/* are in ANSI Mode ? */ \
	if(flash_setting_read(SETTING_DECANM)) \
	{ \
		uart_send( flash_setting_read(SETTING_DECCKM) ? 'O' : '['); \
	} \
	 \
	uart_send(ident); \
	keyclick_sound()

void kbd_decode()
{
	uint8_t ch = 0;
	
	if(kbd.param < KBD_SCANCODE_SIZE)
	{
		switch((uint16_t)kbd_scancode[kbd.param].callback)
		{
			/* only caps is latched */
			case 1:
				if(kbd_latch_read(KBD_CAPS | KBD_CTRL) == KBD_CAPS)
				{
					ch = 1;
				}
							
			case 0:
				if(kbd_latch_read(KBD_BREAK))
				{
					break;
				}
				
				if(kbd_latch_read(KBD_SHIFT | KBD_CTRL))
				{
					ch ^= 1;
				}
				
				ch = kbd_scancode[kbd.param].ch[ch];
				
				if(kbd_latch_read(KBD_CTRL))
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
		
		kbd_latch_low(KBD_BREAK | KBD_MODIFIER);
	}
	else
	{
		switch(kbd.param)
		{
			case 0xF0:
				/* some key released */
				kbd_latch_high(KBD_BREAK);
			break;
			
			case 0xE0:
				kbd_latch_high(KBD_MODIFIER);
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
	if(!kbd_latch_read(KBD_BREAK))
	{
		kbd_latch_flip(KBD_CAPS);
		keyclick_sound();
	}
}

void kbd_shift()
{
	if(kbd_latch_read(KBD_BREAK))
	{
		kbd_latch_low(KBD_SHIFT);
	}
	else
	{
		kbd_latch_high(KBD_SHIFT);
	}
}
		
void kbd_ctrl()
{
	if(kbd_latch_read(KBD_BREAK))
	{
		kbd_latch_low(KBD_CTRL);
	}
	else
	{
		kbd_latch_high(KBD_CTRL);
	}
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
	if(kbd_latch_read(KBD_MODIFIER))
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
	
	keyclick_sound();
}

void
kbd_enter()
{
	break_event_stop();
	
	if(kbd_latch_read(KBD_MODIFIER) && flash_setting_read(SETTING_DECKPAM))
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

void kbd_break()
{
	
}

