#include <interrupt/port2.h>

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
			cqueue_push(&keyboard_ps2.queue, keyboard_ps2.data);
			keyboard_ps2.index = -2;
		break;
	}
}
