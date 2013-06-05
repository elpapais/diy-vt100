#include <state-machine.h>
#include <param.h>

#include <vt100/attribute.h>
#include <vt100/bell.h>
#include <vt100/buffer.h>
#include <vt100/cursor.h>
#include <vt100/led.h>
#include <vt100/margin.h>
#include <vt100/misc.h>
#include <vt100/report.h>
#include <vt100/screen.h>
#include <vt100/tab.h>
#include <vt100/state.h>

const struct __state
vt100_state_C0[] = 
{
	state_noparam	(0, vt100_state_worker),
	
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_noparam	(ASCII_BELL, vt100_BEL),
	state_noparam	(ASCII_TAB, vt100_HT),
	state_param		(ASCII_BS, vt100_CUB, 1, 1),
	/* TODO: LNM: newline mode, no mode, default applied */
	state_noparam	(ASCII_LF, vt100_LF),
	state_noparam	(ASCII_CR, vt100_CR),
	state_ignore	(ASCII_DEL),
	state_ignore	(ASCII_NULL),
	//func_call_noparam(ASCII_ENQ, vt100_identity), is ASCII_ENQ alias of ESC Z ??
	state_end		()
};

const struct __state
vt100_state_C1[] = //ESC
{
	state_noparam	(0, vt100_state_worker),
	
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_select	('[', vt100_state_opensquarebracket),
	state_select	('#', vt100_state_hash),
	state_noparam	('Z', vt100_DECID),
	state_param		('=', vt100_DECKPAM, 1, 1),
	state_param		('>', vt100_DECKPAM, 1, 0),
	state_noparam	('8', vt100_DECRC),
	state_noparam	('7', vt100_DECSC),
	state_noparam	('H', vt100_HTS),
	state_noparam	('D', vt100_IND),
	state_noparam	('E', vt100_NEL),
	state_noparam	('M', vt100_RI),
	state_noparam	('c', vt100_RIS),
	state_end		()
};

const struct __state
vt100_state_open_smallbracket[] = //(
{
	state_noparam	(0, vt100_state_worker),

	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_end()
};

const struct __state
vt100_state_close_smallbracket[] = //)
{
	state_noparam	(0, vt100_state_worker),
	
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_end()
};

const struct __state
vt100_state_opensquarebracket[] = //[
{
	state_noparam	(0, vt100_state_worker),
	
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_param		('D', vt100_CUB, 1, 1),
	state_param		('B', vt100_CUD, 1, 1),
	state_param		('C', vt100_CUF, 1, 1),
	state_param		('A', vt100_CUU, 1, 1),
	state_param		('H', vt100_CUP, 2, 0),
	state_param		('f', vt100_HVP, 2, 0),
	state_noparam	('c', vt100_DECID),
	state_param		('q', vt100_DECLL, PARAM_QUEUE_SIZE, 0),
	state_param		('r', vt100_DECSTBM, 2, 0),
	state_noparam	('y', vt100_DECTST),
	state_param		('J', vt100_ED, 1, 0),
	state_param		('K', vt100_EL, 1, 0),
	state_param		('m', vt100_SGR, PARAM_QUEUE_SIZE, 0),
	state_param		('n', vt100_DSR, 1, 0),
	state_param		('x', vt100_DECREPTPARAM, 1, 0),
	state_param		('g', vt100_TBC, 1,0),
	state_end		()
};

const struct __state
vt100_state_hash[] = //#
{
	state_noparam	(0, vt100_state_worker),
	
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_noparam	('3', vt100_DECDHL_top),
	state_noparam	('4', vt100_DECDHL_bottom),
	state_noparam	('5', vt100_DECDWL),
	state_noparam	('8', vt100_DECALN),
	state_end		()
};

const struct __state
vt100_state_question[] = //?
{
	state_noparam	(0, vt100_state_worker),
	
	//state_noparam	('l', vt100_DEC_l),
	//state_noparam	('h', vt100_DEC_h),
	state_end		()
};

void vt100_state_worker()
{
	if(state_iterate->cb != 0)
	{
		if(state_iterate->cb == (callback_t)2)
		{
			/* select state */
			state_current = (struct __state *)state_iterate->arg.state;
		}
		/* clear out ignore states */
		else if(state_iterate->cb != (callback_t)1)
		{
			/* NOTE: can become a bug if function with state used, currently we only support param's */
			state_current = (struct __state *)vt100_state_C0;
			param_default(state_iterate->arg.param.pcount, state_iterate->arg.param.pdefault);
			state_iterate->cb();
			/* reset param */
			param.count = 0;
		}
	}
	/* if we are at start state, store it in buffer */
	else if(state_current == (struct __state *)vt100_state_C0)
	{
		vt100_buffer_putchar();
	}
	else
	{
		/* try to use missing items as param */
		param_add();
	}
}
