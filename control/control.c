#include <control.h>

static struct __control
*control_current = (struct __control *)control_C0;

void
control()
{
	struct __control *i;
	
	/* search for recv in __block table */
	for(i=control_current; i->cb; i++)
	{
		if(i->ch != vt100_param.pass)
		{
			continue;
		}
		
		if(i->cb == (const callback_t)1)
		{
			control_current = (struct __control *)i->arg.select;
		}
		else if(i->cb != (const callback_t)2)
		{
			vt100_param_default(i->arg.param.pcount, 
								i->arg.param.pdefault);
			i->cb();
			vt100_param.count = 0;
		}
		
		break;
	}
	
	/* no attached callback found */
	if(i->cb == 0)
	{
		/* if we are at start state, store it in buffer */
		if(control_current == control_C0)
		{
			vt100_buffer_putchar();
		}
		else
		{
			/* assuming this as paramter */
			vt100_param_add();
		}
	}
	else if(i->cb != (callback_t)1)
	{
		/* at the end of execution, revert to start state, 
		 *  ignore unknown paramters
		 */
		control_current = (struct __control *)control_C0;
	}
}
