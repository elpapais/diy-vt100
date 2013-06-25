#include <diy-vt100/hardware/port2.h>
#include <diy-vt100/hardware/keyboard.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/hardware/cqueue.h>

void port2_init(void)
{
	P2DIR &= ~(KEYBOARD_PS2_DATA | KEYBOARD_PS2_CLK);
	P2REN |= KEYBOARD_PS2_DATA | KEYBOARD_PS2_CLK;
	P2OUT |= KEYBOARD_PS2_DATA | KEYBOARD_PS2_CLK;
	
	P2IFG &= ~KEYBOARD_PS2_CLK;
	
	P2IES |= KEYBOARD_PS2_CLK;
	P2IE |= KEYBOARD_PS2_CLK;
	
	/* interrupt goes to pin2_interrupt() */

	/* output port */
	P2DIR |= NOKIA1100_SS | NOKIA1100_CLK | NOKIA1100_MOSI;
	P2OUT |= NOKIA1100_SS;

	/* debugging */
	P1DIR |= BIT6;
	P1OUT &= ~BIT6;
}

void port2_interrupt(void)
{
	__flip(P1OUT, BIT6);
	
	__low(P2IFG, KEYBOARD_PS2_CLK);
	
	switch(hw_kbd.index)
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
			hw_kbd.data >>= 1;
			if(__read(P2IN,KEYBOARD_PS2_DATA))
			{
				__high(hw_kbd.data, BIT7);
				//hw_kbd.latch ^= KBD_PARITY;
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
			cqueue_push(&hw_kbd.queue, hw_kbd.data);
			__bic_status_register_on_exit(LPM1_bits);
		default:
			hw_kbd.index = 0;
		return;
	}
	
	hw_kbd.index++;
}
