#include <control.h>

static struct __control
*current_control = (struct __control *)control_C0;

void
control()
{
	struct __control *i;
	
	/* search for recv in __block table */
	for(i=current_control; i->cb; i++)
	{
		if(i->ch != vt100.data)
		{
			continue;
		}
		
		if(i->cb == (callback_t)1)
		{
			current_control = (struct __control *)i->arg.select;
		}
		else
		{
			vt100_param_default(i->arg.param.pcount, i->arg.param.pdefault);
			i->cb();
			vt100_param_reset();
		}
		
		break;
	}
	
	/* is it not found */
	if(i->cb == 0)
	{
		/* if we are at start state, store it in buffer */
		if(current_control == control_C0)
		{
			vt100_buffer_putchar();
		}
		
		/* assuming this as paramter */
		else if(! vt100_param_add())
		{
			return;
		}
	}
	else if(i->cb != (callback_t)1)
	{
		/* at the end of execution, revert to start state, | ignore unknown paramters */
		current_control = (struct __control *)control_C0;
	}
}
