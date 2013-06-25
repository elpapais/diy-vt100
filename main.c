#include <diy-vt100/hardware.h>
#include <diy-vt100/common.h>
#include <diy-vt100/screen.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/vt100/misc.h>
#include <diy-vt100/setting.h>

void msp430_init();

void
main(void)
{
	hardware_init();
	setting_init();
	uart_init(parm_setting.bits.PARITY, parm_setting.bits.PARITYSENSE, parm_setting.uart_rx, parm_setting.uart_tx);
	vt100_init();
	screen_init();
	
	screen_brightness(parm_setting.brightness);
	screen_invert(parm_setting.bits.DECSCNM);
	
	/* show splash screen */
	screen_splash();
	
	hardware_loop();
}
