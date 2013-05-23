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
	vt100_setting.mode ^= VT100_SETTING_MODE_CURSOR_STATE;
	
	/* exit sleep mode to refresh screen */
	__bic_status_register_on_exit(LPM1_bits);
}
