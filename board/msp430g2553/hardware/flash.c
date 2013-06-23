#include <diy-vt100/setting.h>

const setting_t parm_setting =
{
	.vr_bits = 0,
	.brightness = 3,
	.uart_rx = 0, /* 9600 */
	.uart_tx = 0, /* 9600 */
	.nvr_bits = __setting_get_actual_bitmask(SETTING_DECSCLM)
	| __setting_get_actual_bitmask(SETTING_DECARM)
	| __setting_get_actual_bitmask(SETTING_KEYCLICK)
	| __setting_get_actual_bitmask(SETTING_AUTOX)
	| __setting_get_actual_bitmask(SETTING_BPC) ,

	.tabs = 0b1000100010001000,
	.answerback = {'d', 'i', 'y', '-', 'v', 't', '1', '0', '0'}
};

/*
 * flash @ 4MHz/13 = 307692Hz
 * clocked from SMCLK
 */

void setting_init()
{
	FCTL2 = FWKEY + FSSEL_2 + (FN2|FN3);
	setting_load();
}

void setting_store()
{
	register setting_t *dest = (setting_t *)(&parm_setting);

	__disable_interrupt();

	FCTL1 = FWKEY + ERASE;
	FCTL3 = FWKEY;

	dest->vr_bits = 0;

	FCTL1 = FWKEY + WRT;

	*dest = setting;

	FCTL1 = FWKEY;
	FCTL3 = FWKEY + LOCK;

	__enable_interrupt();
}

void setting_load()
{
	setting = (setting_t)parm_setting;
	setting.vr_bits = 0;
}
