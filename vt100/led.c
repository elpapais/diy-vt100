#include <vt100/led.h>
#include <param.h>
#include <hardware/ic_74xx595.h>

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
				ic_74xx595_low(VT100_LED_L1 | VT100_LED_L2 | VT100_LED_L3 | VT100_LED_L4);
			break;
			
			case 1:
				ic_74xx595_high(VT100_LED_L1);
			break;
			
			case 2:
				ic_74xx595_high(VT100_LED_L2);
			break;
			
			case 3:
				ic_74xx595_high(VT100_LED_L3);
			break;
			
			case 4:
				ic_74xx595_high(VT100_LED_L4);
			break;
		}
	}
}
