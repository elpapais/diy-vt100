#include <diy-vt100/bell.h>
#include <diy-vt100/msp430g2553/ic_74xx595.h>

/* note on naming convention
 * timerX_YZ
 * X = instance number (0, 1, 2, ...) , depends on the number of timers
 * Y = timer type (A, B, D ...)
 * Z = no of capture/compare registers
 *
 * append registers_name with "_"
 */

#define TIMER0_A3_TACTL TA0CTL
#define TIMER0_A3_TACCR0 TA0CCR0
#define TIMER0_A3_TACCR1 TA0CCR1
#define TIMER0_A3_TACCTL0 TA0CCTL0

void timer0_A3_start(const uint16_t delay);
void timer0_A0_interrupt (void) __attribute__((interrupt(TIMER0_A0_VECTOR)));

void bell_short(void)
{
	timer0_A3_start(0x4000);
}

void bell_long(void)
{
	timer0_A3_start(0xFFFF);
}

void timer0_A3_start(const uint16_t delay)
{
	ic_74xx595.buzzer = TRUE;
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

void timer0_A0_interrupt(void)
{
	/* turn off buzzer */
	ic_74xx595.buzzer = FALSE;
	ic_74xx595_refresh();
	
	TIMER0_A3_TACTL = TACLR;
}
