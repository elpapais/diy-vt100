#include <vt100/led.h>
#include <param.h>
#include <hardware/led.h>

/* load led's */
void 
vt100_DECLL()
{
	uint8_t i;
	
	for(i=0; i < param.count; i++)
	{
		switch(param.data[i])
		{
			case 0:
				led_off(LED_L1 | LED_L2 | LED_L3 | LED_L4);
			break;
			
			case 1:
				led_on(LED_L1);
			break;
			
			case 2:
				led_on(LED_L2);
			break;
			
			case 3:
				led_on(LED_L3);
			break;
			
			case 4:
				led_on(LED_L4);
			break;
		}
	}
	
	led_refresh();
}
