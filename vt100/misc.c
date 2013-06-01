#include <vt100/misc.h>
#include <vt100/cursor.h>
#include <param.h>
#include <vt100/buffer.h>
#include <vt100/state.h>
#include <vt100/bell.h>
#include <vt100/led.h>
#include <state-machine.h>

uint8_t vt100_setting;

void vt100_init()
{
	/* TODO: load setting from eeprom */
	vt100_bell_init();
	
	vt100_led_init();
	
	/* TODO: check power online/offline mode & keyboard connected */
	/* TODO: support offline mode */
	/* TODO: support Keyboard lock */

	param.data[0] = 2;
	vt100_ED();
	
	state_current = (struct __state *)vt100_state_C0;
}

bool_t __is_vt100_malfunctioning()
{
	return FALSE;
}

/* invoke self confidence test */
void 
vt100_DECTST()
{
	/* TODO: test the terminal */
}

void
vt100_setting_load(void *dest, uint8_t size)
{	
}

void
vt100_setting_save(void *src, uint8_t size)
{
}

/* keypad application mode */
void
vt100_DECKPAM()
{
	vt100_setting |= VT100_SETTING_KEYPAD;
}

/* keypad numberic mode */
void
vt100_DECKPNM()
{
	vt100_setting &= ~VT100_SETTING_KEYPAD;
}

/* reset to inital state (as on power on) */
void 
vt100_RIS()
{
	/* TODO: set vt100 to reset state  */
}
