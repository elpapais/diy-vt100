#include <diy-vt100/param.h>

struct __param param;

/* TODO: check for overflow */
void param_add()
{
	/* prevent overflow */
	if(!(param.count < PARAM_QUEUE_SIZE))
	{
		return;
	}
	
	/* parse the parameters and add it to list */
	if( PARAM_DELIMITER == param.pass)
	{
		param.data[param.count++] = 0;
	}
	else if(param.pass >= '0' && param.pass <= '9') /* is digit, else ignore */
	{
		if(! param.count)
		{
			param.count = 1;
			param.data[0] = 0;
		}
		
		param.data[param.count - 1] = (param.data[param.count - 1] * 10) + param.pass - '0';
	}
	//else
	//{
		/* could not parse the parameter | it isnt a digit */
		//return FALSE;
	//}
	
	//return TRUE;
}

void param_default(int8_t pcount, uint8_t pdefault)
{
	if(param.count >= pcount)
	{
		param.count = pcount;
	}
	else
	{
		/* pad in some default param */
		while(param.count < pcount)
		{
			param.data[param.count++] = pdefault;
		}
	}
}
