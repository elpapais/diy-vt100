#include <hardware/port2.h>

void port2_init()
{
	KEYBOARD_PS2_PDIR &= ~(KEYBOARD_PS2_DATA | KEYBOARD_PS2_CLK);
	KEYBOARD_PS2_PREN |= KEYBOARD_PS2_DATA | KEYBOARD_PS2_CLK;
	KEYBOARD_PS2_POUT |= KEYBOARD_PS2_DATA | KEYBOARD_PS2_CLK;
	
	KEYBOARD_PS2_PIFG &= ~KEYBOARD_PS2_CLK;
	
	KEYBOARD_PS2_PIES |= KEYBOARD_PS2_CLK;
	KEYBOARD_PS2_PIE |= KEYBOARD_PS2_CLK;
	
	P1DIR |= BIT6;
	P1OUT &= ~BIT6;
	/* interrupt goes to pin2_interrupt() */
}

void port2_interrupt()
{
	P1OUT ^= BIT6;
	
	KEYBOARD_PS2_PIFG &= ~KEYBOARD_PS2_CLK;
	
	switch(keyboard_ps2.index)
	{
		case 0:
			/* start bit */
			//keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_PARITY;
		break;
		
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			/* data */
			keyboard_ps2.data >>= 1;
			if(KEYBOARD_PS2_PIN & KEYBOARD_PS2_DATA)
			{
				keyboard_ps2.data |= BIT7;
				//keyboard_ps2.mode ^= KEYBOARD_PS2_MODE_PARITY;
			}
		break;
		
		case 9:
			//if((!(KEYBOARD_PS2_PIN & KEYBOARD_PS2_DATA)) == (!keyboard_ps2.mode & KEYBOARD_PS2_MODE_PARITY))
			//{
				//parity error
				/* TODO: check parity for data */
			//}
		break;
		
		case 10:
			/* STOP bit */
			cqueue_push(&keyboard_ps2.data_queue, keyboard_ps2.data);
			__bic_status_register_on_exit(LPM1_bits);
		default:
			keyboard_ps2.index = 0;
		return;
	}
	
	keyboard_ps2.index++;
}
