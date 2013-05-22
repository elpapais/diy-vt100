#include <hardware/timerA.h>

void timerA_init()
{
	TACTL = TASSEL_2 + ID_3  + MC_1;
	
	/* A0 */
	TACCR0 = 0xFFFF;
	TACCTL0 = CCIE;
	
	/* interrupt goes to timerA0_interrupt() @ 7Hz */
}

void timerA0_interrupt()
{
	vt100.mode.cursor_state ^= TRUE;
	
	/* exit sleep mode to refresh screen */
	__bic_status_register_on_exit(LPM1_bits);
}
