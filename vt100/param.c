#include <vt100/param.h>

/* Parameters parsing */

/* TODO: check for overflow */
bool_t vt100_param_add()
{
	/* parse the parameters and add it to list */
	if( VT100_PARAM_DELIMITER == vt100.data)
	{
		vt100.param[0]++;
		vt100.param[vt100.param[0]] = 0;
	}
	else if(vt100.data >= '0' && vt100.data <= '9') /* is digit, else ignore */
	{
		if(! vt100.param[0])
		{
			vt100.param[0] = 1;
			vt100.param[1] = 0;
		}
		
		vt100.param[vt100.param[0]] = (vt100.param[vt100.param[0]] * 10) + vt100.data - '0';
	}
	else
	{
		return FALSE; /* could not parse the parameter | it isnt a digit */
	}
	
	return TRUE;
}

void vt100_param_default(uint8_t pcount, uint8_t default_value)
{
	if(pcount >= vt100.param[0])
	{
		vt100.param[0] = pcount;
		return;
	}
	
	while(pcount > vt100.param[0])
	{
		vt100.param[pcount--] = default_value;
	}
}
