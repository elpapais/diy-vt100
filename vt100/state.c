#include <diy-vt100/vt100/attribute.h>
#include <diy-vt100/vt100/buffer.h>
#include <diy-vt100/vt100/cursor.h>
#include <diy-vt100/vt100/margin.h>
#include <diy-vt100/vt100/report.h>
#include <diy-vt100/vt100/tab.h>
#include <diy-vt100/vt100/state.h>
#include <diy-vt100/vt100/misc.h>

#include <diy-vt100/vt52/misc.h>

#include <diy-vt100/param.h>
#include <diy-vt100/bell.h>

void vt100_sequence_terminate(void);

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

extern const struct __state vt100_state_C0[];
extern const struct __state vt100_state_C1[];
extern const struct __state vt100_state_hash[];
extern const struct __state vt100_state_question[];
extern const struct __state vt100_state_open_smallbracket[];
extern const struct __state vt100_state_opensquarebracket[];
extern const struct __state vt100_state_close_smallbracket[];

#define state_state(ch, func, _state) 	{func, ch, .arg = {.state = _state}}
#define state_param(ch, func, pc, pd) 	{func, ch, .arg = {.param = {.pcount = pc, .pdefault = pd}}}
#define state_end() 					{0}

/* some useful derivative */
#define state_noparam(ch, func) 		state_param(ch, func, 0, 0)
#define state_maxparam(ch, func, pc, pd)state_param(ch, func, pc, pd)
#define state_minparam(ch, func, pc, pd)state_param(ch, func, (-1 * pc), pd)
#define state_ignore(ch)				state_state(ch, (callback_t)1, 0)
#define state_select(ch, state)			state_state(ch, (callback_t)2, state)

const struct __state
vt100_state_C0[] =
{
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),

	state_noparam	(ASCII_BELL, bell_long),
	state_noparam	(ASCII_TAB, vt100_HT),
	state_maxparam	(ASCII_BS, vt100_CUB, 1, 1),
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
	state_maxparam	('=', vt100_DECKPAM, 1, 1),
	state_maxparam	('>', vt100_DECKPAM, 1, 0),
	state_noparam	('<', vt52_enter_ansi_mode),
	state_maxparam	('A', vt100_CUU, 1, 1),
	state_maxparam	('B', vt100_CUD, 1, 1),
	state_maxparam	('C', vt100_CUF, 1, 1),
	state_maxparam	('D', vt100_CUB, 1, 1),
	state_maxparam	('H', vt100_CUP, 2, 0),
	state_noparam	('I', vt100_RI),
	state_noparam	('Z', vt52_ident),

	state_end		()
};

const struct __state
vt100_state_open_smallbracket[] = //(
{
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_end()
};

const struct __state
vt100_state_close_smallbracket[] = //)
{
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_end		()
};

const struct __state
vt100_state_opensquarebracket[] = //[
{
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	state_select	(ASCII_ESCAPE, vt100_state_C1),
	state_select	('?', vt100_state_question),

	state_maxparam	('D', vt100_CUB, 1, 1),
	state_maxparam	('B', vt100_CUD, 1, 1),
	state_maxparam	('C', vt100_CUF, 1, 1),
	state_maxparam	('A', vt100_CUU, 1, 1),
	state_maxparam	('H', vt100_CUP, 2, 0),
	state_maxparam	('f', vt100_CUP, 2, 0), /* vt100_HVP */
	state_noparam	('c', vt100_DECID),
	state_minparam	('q', vt100_DECLL, 1, 0),
	state_maxparam	('r', vt100_DECSTBM, 2, 0),
	state_noparam	('y', vt100_DECTST),
	state_maxparam	('J', vt100_ED, 1, 0),
	state_maxparam	('K', vt100_EL, 1, 0),
	state_minparam	('m', vt100_SGR, 1, 0),
	state_maxparam	('n', vt100_DSR, 1, 0),
	state_maxparam	('x', vt100_DECREPTPARAM, 1, 0),
	state_maxparam	('g', vt100_TBC, 1,0),
	state_maxparam	('h', vt100_setting_high, 1, 0),
	state_maxparam	('l', vt100_setting_low, 1, 0),
	state_end		()
};

const struct __state
vt100_state_hash[] = //#
{
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
	state_noparam	(ASCII_CAN, vt100_sequence_terminate),
	state_noparam	(ASCII_SUB, vt100_sequence_terminate),
	state_minparam	('l', vt100_setting_low, 1, 0),
	state_minparam	('h', vt100_setting_high, 1, 0),
	state_end		()
};

void vt100_state(const uint8_t data)
{
	static struct __state *current = (struct __state *)vt100_state_C0;
	struct __state *iterate;
	
	for(iterate = current; iterate->cb; iterate++)
	{
		if(iterate->ch == data)
		{
			break;
		}
	}
	
	if(iterate->cb != 0)
	{
		if(iterate->cb == (callback_t)2)
		{
			/* select state */
			current = (struct __state *)iterate->arg.state;
		}
		/* clear out ignore states */
		else if(iterate->cb != (callback_t)1)
		{
			/* NOTE: can become a bug if function with state used
			 * currently we only support param's */
			current = (struct __state *)vt100_state_C0;

			/* chop of extra param */
			param_default(iterate->arg.param.pcount,
							iterate->arg.param.pdefault);

			iterate->cb();

			/* reset param */
			param.count = 0;
		}
	}
	
	/* if we are at start state, store it in buffer */
	else if(current == (struct __state *)vt100_state_C0)
	{
		vt100_putch(data);
	}
	
	else
	{
		/* try to use missing items as param */
		param_add(data);
	}
}

void vt100_sequence_terminate()
{
	/* reset to C0 state (this work is already preformed by worker function) */
	//state_current = (struct __state)vt100_state_C0;

	/* TODO: print error char */
}
