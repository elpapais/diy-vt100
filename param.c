#include <diy-vt100/param.h>

param_t param;

/* TODO: check for overflow */
void param_add(const uint8_t data)
{
	/* prevent overflow */
	if(!(param.count < PARAM_QUEUE_SIZE))
	{
		return;
	}
	
	/* parse the parameters and add it to list */
	if(PARAM_DELIMITER == data)
	{
		param.data[param.count++] = 0;
	}
	else if(data >= '0' && data <= '9') /* is digit, else ignore */
	{
		if(! param.count)
		{
			param.count = 1;
			param.data[0] = 0;
		}
		
		param.data[param.count - 1] *= 10;
		param.data[param.count - 1] += data - '0';
	}
	//else
	//{
		/* could not parse the parameter | it isnt a digit */
		//return FALSE;
	//}
	
	//return TRUE;
}

void param_default(const int8_t pcount, const uint8_t pdefault)
{
	if(pcount < 0)
	{
		/* pad in some default param */
		while(param.count < (pcount*-1))
		{
			param.data[param.count++] = pdefault;
		}
	}
	else
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
}
