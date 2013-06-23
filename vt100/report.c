#include <diy-vt100/vt100/report.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/param.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/vt100/misc.h>
#include <diy-vt100/setting.h>

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
	if(parm_setting_read(SETTING_PARITY))
	{
		uart_send(parm_setting_read(SETTING_PARITYSENSE) ? '5' : '4');
	}
	else
	{
		/* is this required?? */
		uart_send('0');
	}
	
	uart_send(';');
	uart_send((parm_setting_read(SETTING_BPC)) ? '1' : '2');
	
	uart_send(';');
	uart_send_array( &uart_speed[setting.uart_tx].value[1], 
						uart_speed[setting.uart_tx].value[0]);
	
	uart_send(';');
	uart_send_array( &uart_speed[setting.uart_rx].value[1], 
						uart_speed[setting.uart_rx].value[0]);
	
	uart_send(';');
	uart_send(uart_clkmul);
	
	uart_send(';');
	uart_send('0');
	
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
