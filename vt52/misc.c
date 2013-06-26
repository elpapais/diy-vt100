#include <diy-vt100/vt52/misc.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/setting.h>

void vt52_ident()
{
	uart_send(ASCII_ESCAPE);
	uart_send('/');
	uart_send('Z');
}

void vt52_enter_ansi_mode()
{
	setting.bits.DECANM = TRUE;
}
