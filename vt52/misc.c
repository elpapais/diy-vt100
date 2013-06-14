#include <vt52/misc.h>
#include <uart.h>
#include <setting.h>

void vt52_ident()
{
	uart_send_escape();
	uart_send('/');
	uart_send('Z');
}

void vt52_enter_ansi_mode()
{
	setting_high(SETTING_DECANM);
}
