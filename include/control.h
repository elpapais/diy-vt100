#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <common.h>
#include <vt100/report.h>
#include <vt100/attribute.h>

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
#define control_end() {0}

void control() __attribute__((interrupt(USCIAB0RX_VECTOR))); /* USCI_A_RX */
#endif
