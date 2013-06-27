#include <diy-vt100/vt100/report.h>
#include <diy-vt100/uart.h>
#include <diy-vt100/param.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/vt100/misc.h>
#include <diy-vt100/setting.h>
#include <diy-vt100/hardware.h>

/* report terminal parameter (requested via DECREQTPARAM) */
void
vt100_DECREPTPARAM()
{
	setting.bits.UNSOLIC = param.data[0] ? FALSE : TRUE;
	
	uart_send(ASCII_ESCAPE);
	uart_send('[');
	
	uart_send_uint8(3);
	
	uart_send(';');
	/* parity info's */
	if(parm_setting.bits.PARITY)
	{
		uart_send(parm_setting.bits.PARITYSENSE ? '5' : '4');
	}
	else
	{
		/* is this required?? */
		uart_send('0');
	}
	
	uart_send(';');
	uart_send(parm_setting.bits.BPC ? '1' : '2');
	
	uart_send(';');
	uart_send_array( &uart_speed[parm_setting.uart_tx].value[1], 
						uart_speed[parm_setting.uart_tx].value[0]);
	
	uart_send(';');
	uart_send_array( &uart_speed[parm_setting.uart_rx].value[1], 
						uart_speed[parm_setting.uart_rx].value[0]);
	
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
	uart_send(ASCII_ESCAPE);
	uart_send('[');
	
	switch(param.data[0])
	{
		case 5:
			/* report status 
			 * sending using DSR control sequence */
			uart_send(hardware_malfunctioning() ? '0' : '3');
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
	uart_send(ASCII_ESCAPE);
	uart_send('[');
	uart_send('?');
	uart_send('1');
	uart_send(';');
	uart_send('2');
	uart_send('c');
}
