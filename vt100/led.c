#include <vt100/led.h>
#include <param.h>

void
vt100_led_init()
{
	/* LED */
	VT100_LED_PDIR |= 	VT100_LED_ONLINE | 
						VT100_LED_LOCAL |
						VT100_LED_KBDLOCK |
						VT100_LED_L1 |
						VT100_LED_L2 |
						VT100_LED_L3 |
						VT100_LED_L4;

	VT100_LED_POUT |= VT100_LED_ONLINE;
}

void 
vt100_led_load()
{
	uint8_t i;
	/* TODO: support for led */
	for(i=0; i < param.count; i++)
	{
		switch(param.data[0])
		{
			case 0:
				VT100_LED_POUT &= ~(VT100_LED_L1 | VT100_LED_L2 | VT100_LED_L3 | VT100_LED_L4);
			break;
			
			case 1:
				VT100_LED_POUT |= VT100_LED_L1;
			break;
			
			case 2:
				VT100_LED_POUT |= VT100_LED_L2;
			break;
			
			case 3:
				VT100_LED_POUT |= VT100_LED_L3;
			break;
			
			case 4:
				VT100_LED_POUT |= VT100_LED_L4;
			break;
			
			//default:
				//ignore
		}
	}
}
