#include <hardware/wdt.h>
#include <setting.h>

uint8_t wdt_cycles;

void wdt_init()
{
	WDTCTL = WDT_MDLY_32;
	IE1 |= WDTIE;
}

void wdt_interrupt()
{
	if(!(++wdt_cycles < WDT_CYCLES_MAX))
	{
		setting_flip(SETTING__CURSOR_STATE);
	
		wdt_cycles = 0;
		
		/* exit sleep mode to refresh screen */
		__bic_status_register_on_exit(LPM1_bits);
	}
}
