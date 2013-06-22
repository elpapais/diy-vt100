#ifndef _STATE_H_
#define _STATE_H_

#include <diy-vt100/common.h>

/* note: 0 index is selected in case no match found */
struct __state
{
	const callback_t cb;
	const uint8_t ch;
	
	union
	{
		struct
		{
			const int8_t pcount;
			const uint8_t pdefault;
		} param;
		
		const struct __state *state;
	} arg;
};

extern struct __state *state_current;
extern struct __state *state_iterate;

#define state_worker(func)				{func, 0}
#define state_state(ch, func, _state) 	{func, ch, .arg = {.state = _state}}
#define state_param(ch, func, pc, pd) 	{func, ch, .arg = {.param = {.pcount = pc, .pdefault = pd}}}
#define state_end() 					{0}

/* some useful derivative */
#define state_noparam(ch, func) 		state_param(ch, func, 0, 0)
#define state_maxparam(ch, func, pc, pd)state_param(ch, func, pc, pd)
#define state_minparam(ch, func, pc, pd)state_param(ch, func, (-1 * pc), pd)
#define state_ignore(ch)				state_state(ch, (callback_t)1, 0)
#define state_select(ch, state)			state_state(ch, (callback_t)2, state)
void state_do();
#endif
