#include <diy-vt100/led.h>
#include <diy-vt100/msp430g2553/ic_74xx595.h>

void led_on(led_t led_no)
{
	switch(led_no)
	{
		case LINE:
			ic_74xx595.led_online = TRUE;
		break;
		
		case LOCAL:
			ic_74xx595.led_offline = TRUE;
		break;
		
		case KBDLOCK:
			ic_74xx595.led_kbdlock = TRUE;
		break;
		
		case PROG1:
			ic_74xx595.led_prog1 = TRUE;
		break;
		
		case PROG2:
			ic_74xx595.led_prog2 = TRUE;
		break;
		
		case PROG3:
			ic_74xx595.led_prog3 = TRUE;
		break;
		
		case PROG4:
			ic_74xx595.led_prog4 = TRUE;
		break;
	}
}

void led_off(led_t led_no)
{
	switch(led_no)
	{
		case LINE:
			ic_74xx595.led_online = FALSE;
		break;
		
		case LOCAL:
			ic_74xx595.led_offline = FALSE;
		break;
		
		case KBDLOCK:
			ic_74xx595.led_kbdlock = FALSE;
		break;
		
		case PROG1:
			ic_74xx595.led_prog1 = FALSE;
		break;
		
		case PROG2:
			ic_74xx595.led_prog2 = FALSE;
		break;
		
		case PROG3:
			ic_74xx595.led_prog3 = FALSE;
		break;
		
		case PROG4:
			ic_74xx595.led_prog4 = FALSE;
		break;
	}
}

void led_off_allprog(void)
{
	ic_74xx595.led_prog1 = FALSE;
	ic_74xx595.led_prog2 = FALSE;
	ic_74xx595.led_prog3 = FALSE;
	ic_74xx595.led_prog4 = FALSE;
}
