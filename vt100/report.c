#include <vt100/report.h>

void
vt100_report_parameters()
{
	vt100_setting.mode = vt100_param.data[0] ? \
			vt100_setting.mode & ~(VT100_SETTING_MODE_UNSOLIC_ALLOW) : \
			vt100_setting.mode | VT100_SETTING_MODE_UNSOLIC_ALLOW;
	
	uart_send_escape();
	uart_send('[');
	uart_send_uint8(3);
	uart_send(';');
	uart_send_uint8(1);
	uart_send(';');
	uart_send_uint8(1);
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
vt100_report_DSR()
{
	uart_send_escape();
	uart_send('[');
	
	switch(vt100_param.data[0])
	{
		case 5:
			uart_send(__is_vt100_malfunctioning() ? '0' : '3');
		break;
		
		case 6:
			uart_send_uint8(vt100_cursor.row);
			uart_send(';');
			uart_send_uint8(vt100_cursor.col);
		break;
		//default:
			//problem
	}
	uart_send('n');
}


void vt100_report_identity()
{
	uart_send_escape();
	uart_send('[');
	uart_send('?');
	uart_send('1');
	uart_send(';');
	uart_send('2');
	uart_send('c');
}
