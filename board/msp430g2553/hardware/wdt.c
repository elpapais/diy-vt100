#include <diy-vt100/hardware/wdt.h>
#include <diy-vt100/setting.h>

#define CURSOR_STATE HW_PRIV0

const uint8_t wdt_cycles_max = 64;
uint8_t wdt_cycles;

void wdt_init(void)
{
	WDTCTL = WDT_MDLY_32;
	IE1 |= WDTIE;
}

void wdt_interrupt(void)
{
	if(!(++wdt_cycles < wdt_cycles_max))
	{
		setting.bits.CURSOR_STATE ^= TRUE;
	
		wdt_cycles = 0;
		
		/* exit sleep mode to refresh screen */
		__bic_status_register_on_exit(LPM1_bits);
	}
}
