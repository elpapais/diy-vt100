#include <vt100/report.h>

void
vt100_report_parameters()
{
	vt100.mode.unsolicited_allowed = !vt100_param_get(0);
	
	vt100_param_setcount(6);
	vt100_param_set(0, 3);
	vt100_param_set(1, 1);
	vt100_param_set(2, 1);
	vt100_param_set(3, 112);
	vt100_param_set(4, 16);
	vt100_param_set(5, 0);
	
	uart_send_param('[','x', 0);
}

/* device status report */
void
vt100_DSR()
{
	if(vt100_param_get(0) == 5)
	{
		uart_send_ESCseq( __is_vt100_malfunctioning() ? "[0n" : "[3n");
	}
	else
	{
		vt100_param_setcount(2);
		vt100_param_set(0, vt100.cursor.row);
		vt100_param_set(1, vt100.cursor.col);
		uart_send_param('[', 'n', 1);
	}
}


void vt100_identity()
{
	uart_send_ESCseq("[?1;2c");
}
