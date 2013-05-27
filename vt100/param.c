#include <vt100/param.h>

struct __vt100_param vt100_param;

/* TODO: check for overflow */
void vt100_param_add()
{
	/* parse the parameters and add it to list */
	if( VT100_PARAM_DELIMITER == vt100_param.pass)
	{
		vt100_param.data[++vt100_param.count] = 0;
	}
	else if(vt100_param.pass >= '0' && vt100_param.pass <= '9') /* is digit, else ignore */
	{
		if(! vt100_param.count)
		{
			vt100_param.count = 1;
			vt100_param.data[0] = 0;
		}
		
		vt100_param.data[vt100_param.count] = (vt100_param.data[vt100_param.count] * 10) + vt100_param.pass - '0';
	}
	//else
	//{
		/* could not parse the parameter | it isnt a digit */
	//}
}

void vt100_param_default(uint8_t pcount, uint8_t pdefault)
{
	/* chop of extra param */
	if(vt100_param.count >= pcount)
	{
		vt100_param.count = pcount;
	}
	else
	{
		/* pad in some default param */
		while(vt100_param.count < pcount)
		{
			vt100_param.data[vt100_param.count++] = pdefault;
		}
	}
}
