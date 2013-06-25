#include <diy-vt100/hardware/keyboard.h>
#include <diy-vt100/keyboard.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/bell.h>

#define KBD_MODIFIER HW_PRIV1
#define KBD_BREAK HW_PRIV2

hwkbd_t hw_kbd;

void hw_kbd_decode(void)
{
	register uint8_t ch = 0;

	if(hw_kbd.param < HW_KBD_SCANCODE_SIZE)
	{
		const hwkbdscancode_t *scancode = &hw_kbd_scancode[hw_kbd.param];
		
		switch((uint16_t)scancode->callback)
		{
			/* only caps is latched */
			case 1:
				if(setting.bits.KBD_CAPS && ! setting.bits.KBD_CTRL)
				{
					ch |= 1;
				}

			case 0:
				if(setting.bits.KBD_BREAK)
				{
					break;
				}

				if(setting.bits.KBD_SHIFT || setting.bits.KBD_CTRL)
				{
					ch ^= 1;
				}

				ch = scancode->ch[ch];
				
				keyboard_other(ch);
			break;

			default:
				scancode->callback();
			break;
		}

		setting.bits.KBD_BREAK = FALSE;
		setting.bits.KBD_MODIFIER = FALSE;
	}
	else
	{
		switch(hw_kbd.param)
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

#define break_event_stop()  \
	if(setting.bits.KBD_BREAK) \
	{ \
		return; \
	}


void hw_kbd_f1(void)
{
	break_event_stop();
	keyboard_pfn(PF1);
}

void hw_kbd_f2(void)
{
	break_event_stop();
	keyboard_pfn(PF2);
}

void hw_kbd_f3(void)
{
	break_event_stop();
	keyboard_pfn(PF3);
}

void hw_kbd_f4(void)
{
	break_event_stop();
	keyboard_pfn(PF4);
}

void hw_kbd_f5(void)
{
	break_event_stop();
	keyboard_setup();
}

void hw_kbd_caps(void)
{
	/* caps status modify */
	if(! setting.bits.KBD_BREAK)
	{
		setting.bits.KBD_CAPS ^= TRUE;
		keyboard_keyclick_sound();
	}
}

void hw_kbd_shift(void)
{
	setting.bits.KBD_SHIFT = setting.bits.KBD_BREAK ? FALSE : TRUE;
}

void hw_kbd_ctrl(void)
{
	setting.bits.KBD_CTRL = setting.bits.KBD_BREAK ? FALSE : TRUE;
}

#define hw_kbd_mux_keypad_num_arrow(num, arrow) \
	break_event_stop(); \
	\
	/* arrow key pressed */ \
	if(setting.bits.KBD_MODIFIER) \
	{ \
		keyboard_arrow(arrow); \
	} \
	/* send accoring to Keypad mode */ \
	else \
	{ \
		keyboard_keypad_num(num); \
	}

void hw_kbd_keypad_0(void)
{
	break_event_stop();
	keyboard_keypad_num(0);
}

void hw_kbd_keypad_1(void)
{
	break_event_stop();
	keyboard_keypad_num(1);
}

void hw_kbd_keypad_2(void)
{
	hw_kbd_mux_keypad_num_arrow(2, DOWN);
}

void hw_kbd_keypad_3(void)
{
	break_event_stop();
	keyboard_keypad_num(3);
}

void hw_kbd_keypad_4(void)
{
	hw_kbd_mux_keypad_num_arrow(4, LEFT);
}

void hw_kbd_keypad_5(void)
{
	break_event_stop();
	keyboard_keypad_num(5);
}

void hw_kbd_keypad_6(void)
{
	hw_kbd_mux_keypad_num_arrow(6, RIGHT);
}

void hw_kbd_keypad_7(void)
{
	break_event_stop();
	keyboard_keypad_num(7);
}

void hw_kbd_keypad_8(void)
{
	hw_kbd_mux_keypad_num_arrow(8, UP);
}

void hw_kbd_keypad_9(void)
{
	break_event_stop();
	keyboard_keypad_num(9);
}

void hw_kbd_keypad_dash(void)
{
	break_event_stop();
	keyboard_keypad_dash();
}

void
hw_kbd_keypad_dot(void)
{
	/* below code is a modified version of *keypad(void)
	 * any future update to it , are also carried here too */

	break_event_stop();

	/* arrow key pressed */
	if(setting.bits.KBD_MODIFIER)
	{
		keyboard_delete();
	}
	/* send accoring to Keypad mode */
	else
	{
		keyboard_keypad_dot();
	}
}

void
hw_kbd_enter(void)
{
	break_event_stop();

	/* arrow key pressed */
	if(setting.bits.KBD_MODIFIER)
	{
		keyboard_keypad_enter();
	}
	/* send accoring to Keypad mode */
	else
	{
		keyboard_return();
	}
}

void hw_kbd_break(void)
{

}
