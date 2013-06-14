#include <diy-vt100/hardware/timer0_A3.h>
#include <diy-vt100/hardware/ic_74xx595.h>

/* note on naming convention
 * timerX_YZ
 * X = instance number (0, 1, 2, ...) , depends on the number of timers
 * Y = timer type (A, B, D ...)
 * Z = no of capture/compare registers
 * 
 * append registers_name with "_"
 */

void timer0_A3_start(const uint16_t delay)
{
	ic_74xx595_high(BUZZER);
	ic_74xx595_refresh();
	
	TIMER0_A3_TACCR0 = delay;
	TIMER0_A3_TACCTL0 = CCIE;
	
	/* timer0_A3 @ 512KHz */
	TIMER0_A3_TACTL = TASSEL_2 + ID_3  + MC_1 + TACLR;
	
	/* interrupt goes to timer0_A0_interrupt() */
}

/* note on vector naming convention
 * timerX_YZ
 * X = instance number (0, 1, 2 ...) , depends on the number of timers
 * Y = timer type (A, B, C ....)
 * Z = vector number of timer (_NOT_ number of capture/compare registers)
 */

void timer0_A0_interrupt()
{
	/* turn off buzzer */
	ic_74xx595_low(BUZZER);
	ic_74xx595_refresh();
	TIMER0_A3_TACTL = TACLR;
}
