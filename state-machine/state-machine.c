#include <state-machine.h>
#include <param.h>

struct __state *state_current;
struct __state *state_iterate;

void
state_do()
{
	state_iterate = state_current;
	
	while((++state_iterate)->cb)
	{
		if(state_iterate->ch == param.pass)
		{
			break;
		}
	}
	
	/* first is the worker */
	state_current->cb();
}
