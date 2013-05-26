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
	
	keyboard_ps2.index = -2;
	
	/* interrupt goes to pin2_interrupt() */
}

void port2_interrupt()
{
	P1OUT ^= BIT6;

	keyboard_ps2.index++;
	
	switch(keyboard_ps2.index)
	{
		case -1:
			/* start bit */
			keyboard_ps2.data = 0;
			//keyboard_ps2.mode &= ~KEYBOARD_PS2_MODE_PARITY;
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
				//keyboard_ps2.mode ^= KEYBOARD_PS2_MODE_PARITY;
			}
		break;
		
		case 8:
			//if((!(KEYBOARD_PS2_PIN & KEYBOARD_PS2_DATA)) == (!keyboard_ps2.mode & KEYBOARD_PS2_MODE_PARITY))
			//{
				//parity error
				/* TODO: check parity for data */
			//}
		break;
		
		case 9:
			/* STOP bit */
			keyboard_ps2_data_decode();
			
		default:
			keyboard_ps2.index = -2;
		break;
	}
	
	KEYBOARD_PS2_PIFG &= ~KEYBOARD_PS2_CLK;
}
