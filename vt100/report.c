#include <vt100/report.h>

void
vt100_report_parameters()
{
	vt100_setting.mode = vt100_param.data[0] ? \
				vt100_setting.mode & ~(VT100_SETTING_MODE_UNSOLIC_ALLOW) : \
				vt100_setting.mode | VT100_SETTING_MODE_UNSOLIC_ALLOW;
	
	vt100_param.count = 6;
	vt100_param.data[0] = 3;
	vt100_param.data[1] = 1;
	vt100_param.data[2] = 1;
	vt100_param.data[3] = 112;
	vt100_param.data[4] = 16;
	vt100_param.data[5] = 0;
	
	uart_send_param('[','x', 0);
}

/* device status report */
void
vt100_report_DSR()
{
	if(vt100_param.data[0] == 5)
	{
		vt100_param.count = 4;
		vt100_param.data[0] = ASCII_ESCAPE;
		vt100_param.data[1] = '[';
		vt100_param.data[2] = __is_vt100_malfunctioning() ? '0' : '3';
		vt100_param.data[3] = 'n';
		uart_send_param_direct();
		//uart_send_ESCseq( __is_vt100_malfunctioning() ? "[0n" : "[3n");
	}
	else
	{
		vt100_param.count = 2;
		vt100_param.data[0] = vt100_cursor.row;
		vt100_param.data[1] = vt100_cursor.col;
		uart_send_param('[', 'n', 1);
	}
}


void vt100_report_identity()
{
	vt100_param.count = 7;
	vt100_param.data[0] = ASCII_ESCAPE;
	vt100_param.data[1] = '[';
	vt100_param.data[2] = '?';
	vt100_param.data[3] = '1';
	vt100_param.data[4] = ';';
	vt100_param.data[5] = '2';
	vt100_param.data[6] = 'c';
	uart_send_param_direct();
	//uart_send_ESCseq("[?1;2c");
}
