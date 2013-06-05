#include <hardware/timer0_A3.h>
#include <setting.h>

/* note on naming convention
 * timerX_YZ
 * X = instance number (0, 1, 2, ...) , depends on the number of timers
 * Y = timer type (A, B, D ...)
 * Z = no of capture/compare registers
 * 
 * append registers_name with "_"
 */

void timer0_A3_init()
{
	//TIMER0_A3_TACCR0 = 0xFFFF - 1;
	TIMER0_A3_TACCTL0 = CCIE;
	
	/* timer0_A3 @ 512KHz */
	TIMER0_A3_TACTL = TASSEL_2 + ID_3  + MC_2 + TACLR;
	
	/* interrupt goes to timer0_A0_interrupt() @ 7Hz */
}

/* note on vector naming convention
 * timerX_YZ
 * X = instance number (0, 1, 2 ...) , depends on the number of timers
 * Y = timer type (A, B, C ....)
 * Z = vector number of timer (_NOT_ number of capture/compare registers)
 */

void timer0_A0_interrupt()
{
	setting_flip(SETTING__CURSOR_STATE);
	
	/* exit sleep mode to refresh screen */
	__bic_status_register_on_exit(LPM1_bits);
}
