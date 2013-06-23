#include <diy-vt100/hardware.h>
#include <diy-vt100/common.h>
#include <diy-vt100/keyboard/keyboard.h>
#include <diy-vt100/screen.h>
#include <diy-vt100/param.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/state-machine.h>
#include <diy-vt100/vt100/misc.h>
#include <diy-vt100/setting.h>

void msp430_init();

void
main()
{
	hardware_init();
	setting_init();
	uart_init(parm_setting_ishigh(SETTING_PARITY), parm_setting_ishigh(SETTING_PARITYSENSE), parm_setting.uart_rx, parm_setting.uart_tx);
	vt100_init();
	screen_init();
	
	screen_brightness(parm_setting.brightness);
	screen_invert(parm_setting_ishigh(SETTING_DECSCNM));
	
	/* show splash screen */
	screen_splash();
	
	__loop:
		while(kbd.queue.count)
		{
			kbd.param = cqueue_pop(&kbd.queue);
			kbd_decode();
		}
		
		while(uart_rx.count)
		{
			param.pass = cqueue_pop(&uart_rx);
			state_do();
		}
		
		screen_refresh();
		
		refresh_finished();
	goto __loop;
}
