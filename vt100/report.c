#include <vt100/report.h>
#include <uart.h>
#include <param.h>
#include <setting.h>
#include <vt100/cursor.h>
#include <hardware/flash.h>

/* report terminal parameter (requested via DECREQTPARAM) */
void
vt100_DECREPTPARAM()
{
	if(param.data[0])
	{
		setting_low(SETTING__UNSOLIC);
	}
	else
	{
		setting_high(SETTING__UNSOLIC);
	}
	
	uart_send_escape();
	uart_send('[');
	uart_send_uint8(3);
	uart_send(';');
	
	/* parity info's */
	if(flash_setting_read(SETTING_PARITY))
	{
		uart_send(flash_setting_read(SETTING_PARITYSENSE) ? '5' : '4');
	}
	else
	{
		/* is this required?? */
		uart_send('0');
	}
	
	uart_send(';');
	
	uart_send((flash_setting_read(SETTING_BPC)) ? '1' : '2');
	
	uart_send(';');
	uart_send_uint8(112);
	uart_send(';');
	uart_send_uint8(16);
	uart_send(';');
	uart_send_uint8(0);
	uart_send('x');
}

/* device status report */
void
vt100_DSR()
{
	uart_send_escape();
	uart_send('[');
	
	switch(param.data[0])
	{
		case 5:
			/* report status 
			 * sending using DSR control sequence */
			uart_send(__is_vt100_malfunctioning() ? '0' : '3');
		break;
		
		case 6:
			/* report active position 
			 * sending using CPR control sequence */
			uart_send_uint8(vt100_cursor.row);
			uart_send(';');
			uart_send_uint8(vt100_cursor.col);
		break;
	}
	uart_send('n');
}

/* report device ID
 * identify terminal */
void vt100_DECID()
{
	uart_send_escape();
	uart_send('[');
	uart_send('?');
	uart_send('1');
	uart_send(';');
	uart_send('2');
	uart_send('c');
}
