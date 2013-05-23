#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <common.h>
#include <uart.h>
#include <cqueue.h>
#include <vt100/vt100.h>

struct __control
{
	const callback_t cb;
	const uint8_t ch;
	
	const union
	{
		struct
		{
			const uint8_t pcount;
			const uint8_t pdefault;
		} param;
		
		const struct __control *select;
	} arg;
};

#define control_select(ascii, sel) {(const callback_t)1, ascii, .arg = {.select = sel}}
#define func_call(ascii, func, pc, pd) {(const callback_t)func, ascii, .arg = {.param = {.pcount = pc, .pdefault = pd}}}
#define func_call_noparam(ascii, func) func_call(ascii, func, 0, 0)
#define char_ignore(ascii) func_call(ascii, 2, 0, 0)
#define control_end() {0}

extern const struct __control control_C0[];
extern const struct __control control_open_smallbracket[];
extern const struct __control control_close_smallbracket[];
extern const struct __control control_C1[];
extern const struct __control control_hash[];
extern const struct __control control_opensquarebracket[];

void control_init();
void control();

#endif
