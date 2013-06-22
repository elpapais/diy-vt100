#include <diy-vt100/led.h>
#include <diy-vt100/hardware/ic_74xx595.h>

void led_on(led_t led_no)
{
	switch(led_no)
	{
		case ONLINE:
			ic_74xx595_high(IC_74xx595_PIN1);
		break;
		
		case LOCAL:
			ic_74xx595_high(IC_74xx595_PIN2);
		break;
		
		case KBDLOCK:
			ic_74xx595_high(IC_74xx595_PIN3);
		break;
		
		case PROG1:
			ic_74xx595_high(IC_74xx595_PIN4);
		break;
		
		case PROG2:
			ic_74xx595_high(IC_74xx595_PIN5);
		break;
		
		case PROG3:
			ic_74xx595_high(IC_74xx595_PIN6);
		break;
		
		case PROG4:
			ic_74xx595_high(IC_74xx595_PIN7);
		break;
	}
}

void led_off(led_t led_no)
{
	switch(led_no)
	{
		case ONLINE:
			ic_74xx595_low(IC_74xx595_PIN1);
		break;
		
		case LOCAL:
			ic_74xx595_low(IC_74xx595_PIN2);
		break;
		
		case KBDLOCK:
			ic_74xx595_low(IC_74xx595_PIN3);
		break;
		
		case PROG1:
			ic_74xx595_low(IC_74xx595_PIN4);
		break;
		
		case PROG2:
			ic_74xx595_low(IC_74xx595_PIN5);
		break;
		
		case PROG3:
			ic_74xx595_low(IC_74xx595_PIN6);
		break;
		
		case PROG4:
			ic_74xx595_low(IC_74xx595_PIN7);
		break;
	}
}
