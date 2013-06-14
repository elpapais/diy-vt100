#include <diy-vt100/state-machine.h>
#include <diy-vt100/param.h>

#include <diy-vt100/hardware/led.h>
#include <diy-vt100/hardware/bell.h>

#include <diy-vt100/vt100/attribute.h>
#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/vt100/margin.h>
#include <diy-vt100/vt100/misc.h>
#include <diy-vt100/vt100/report.h>
#include <diy-vt100/vt100/screen.h>
#include <diy-vt100/vt100/tab.h>
#include <diy-vt100/vt100/state.h>

#include <diy-vt100/vt52/misc.h>

const struct __state
vt100_state_C0[] = 
{
	state_noparam	(0, vt100_state_worker),
	
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	state_noparam	(ASCII_BELL, vt100_BEL),
	state_noparam	(ASCII_TAB, vt100_HT),
	state_param		(ASCII_BS, vt100_CUB, 1, 1),
	state_noparam	(ASCII_LF, vt100_LF),
	state_noparam	(ASCII_VT, vt100_LF),
	state_noparam	(ASCII_FF, vt100_LF),
	state_noparam	(ASCII_CR, vt100_CR),
	state_ignore	(ASCII_DEL),
	state_ignore	(ASCII_NULL),
	state_noparam	(ASCII_ENQ, vt100_ENQ),
	state_end		()
};

const struct __state
vt100_state_C1[] = //ESC
{
	state_noparam	(0, vt100_state_worker),
	
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	
	/* conflicting (vt100 & vt52) | TODO: resolve conflicts */
	state_ignore	('D'),
	state_ignore	('H'),
	state_ignore	('Z'),
	
	/* vt100 */
	state_select	('[', vt100_state_opensquarebracket),
	state_select	('#', vt100_state_hash),
	state_noparam	('7', vt100_DECSC),
	state_noparam	('8', vt100_DECRC),
	state_noparam	('c', vt100_RIS),
	state_noparam	('D', vt100_IND),
	state_noparam	('E', vt100_NEL),
	state_noparam	('H', vt100_HTS),
	state_noparam	('M', vt100_RI),
	
	/* vt52 */
	state_param		('=', vt100_DECKPAM, 1, 1),
	state_param		('>', vt100_DECKPAM, 1, 0),
	state_noparam	('<', vt52_enter_ansi_mode),
	state_param		('A', vt100_CUU, 1, 1),
	state_param		('B', vt100_CUD, 1, 1),
	state_param		('C', vt100_CUF, 1, 1),
	state_param		('D', vt100_CUB, 1, 1),
	state_param		('H', vt100_CUP, 2, 0),
	state_noparam	('I', vt100_RI),
	state_noparam	('Z', vt52_ident),
	
	state_end		()
};

const struct __state
vt100_state_open_smallbracket[] = //(
{
	state_noparam	(0, vt100_state_worker),

	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_end()
};

const struct __state
vt100_state_close_smallbracket[] = //)
{
	state_noparam	(0, vt100_state_worker),
	
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_end()
};

const struct __state
vt100_state_opensquarebracket[] = //[
{
	state_noparam	(0, vt100_state_worker),
	
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_param		('D', vt100_CUB, 1, 1),
	state_param		('B', vt100_CUD, 1, 1),
	state_param		('C', vt100_CUF, 1, 1),
	state_param		('A', vt100_CUU, 1, 1),
	state_param		('H', vt100_CUP, 2, 0),
	state_param		('f', vt100_CUP, 2, 0), /* vt100_HVP */
	state_noparam	('c', vt100_DECID),
	state_anyparam	('q', vt100_DECLL),
	state_param		('r', vt100_DECSTBM, 2, 0),
	state_noparam	('y', vt100_DECTST),
	state_param		('J', vt100_ED, 1, 0),
	state_param		('K', vt100_EL, 1, 0),
	state_anyparam	('m', vt100_SGR),
	state_param		('n', vt100_DSR, 1, 0),
	state_param		('x', vt100_DECREPTPARAM, 1, 0),
	state_param		('g', vt100_TBC, 1,0),
	state_param		('h', vt100_setting_high, 1, 0),
	state_end		()
};

const struct __state
vt100_state_hash[] = //#
{
	state_noparam	(0, vt100_state_worker),
	
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
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
	
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	state_param		('l', vt100_setting_low, 1, 0),
	state_param		('h', vt100_setting_high, 1, 0),
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
			/* NOTE: can become a bug if function with state used
			 * currently we only support param's */
			state_current = (struct __state *)vt100_state_C0;
			
			/* chop of extra param */
			param_default(state_iterate->arg.param.pcount, 
							state_iterate->arg.param.pdefault);
			
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
