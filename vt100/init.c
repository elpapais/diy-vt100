#include <vt100/vt100.h>

void vt100_init()
{
	/* TODO: load setting from eeprom */
	vt100_bell_init();
	
	vt100_led_init();
	
	/* TODO: check power online/offline mode & keyboard connected */
	/* TODO: support offline mode */
	/* TODO: support Keyboard lock */
	
	vt100_param_default(1, 2);
	vt100_erase();
}

bool_t __is_vt100_malfunctioning()
{
	return FALSE;
}
