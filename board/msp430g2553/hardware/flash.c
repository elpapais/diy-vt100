#include <diy-vt100/setting.h>

#define CURSOR_STATE HW_PRIV0

const setting_t parm_setting =
{
	.brightness = 3,
	.uart_rx = 0, /* 9600 */
	.uart_tx = 0, /* 9600 */
	.bits =
	{
		.DECSCLM = TRUE,
		.DECARM = TRUE,
		.KEYCLICK = TRUE,
		.AUTOX = TRUE,
		.BPC = TRUE
	},
	.tabs = 0b1000100010001000,
	.answerback = {'d', 'i', 'y', '-', 'v', 't', '1', '0', '0'}
};

/*
 * flash @ 4MHz/13 = 307692Hz
 * clocked from SMCLK
 */

void setting_init(void)
{
	FCTL2 = FWKEY + FSSEL_2 + (FN2|FN3);
	setting_load();
}

void setting_store(void)
{
	register setting_t *dest = (setting_t *)(&parm_setting);

	__disable_interrupt();

	FCTL1 = FWKEY + ERASE;
	FCTL3 = FWKEY;

	dest->tabs = 0;

	FCTL1 = FWKEY + WRT;

	*dest = setting;

	FCTL1 = FWKEY;
	FCTL3 = FWKEY + LOCK;

	__enable_interrupt();
}

void setting_load(void)
{
	setting = (setting_t)parm_setting;

	/* VR */
	setting.bits.DECKPAM = FALSE;
	setting.bits.DECCKM = FALSE;
	setting.bits.DECGON = FALSE;
	setting.bits.DECCOM = FALSE;

	/* PRIVATE - VR */
	setting.bits.UNSOLIC = FALSE;
	setting.bits.LOCAL = FALSE;
	setting.bits.SETUP_TYPE = FALSE;
	setting.bits.SETUP_SHOW = FALSE;


	/* KEYBOARD - VR */
	setting.bits.KBD_SHIFT = FALSE;
	setting.bits.KBD_CTRL = FALSE;
	setting.bits.KBD_CAPS = FALSE;

	/* HW - PRIVATE - VR */
	setting.bits.HW_PRIV0 = FALSE;
	setting.bits.HW_PRIV1 = FALSE;
	setting.bits.HW_PRIV2 = FALSE;
	setting.bits.HW_PRIV3 = FALSE;
}
