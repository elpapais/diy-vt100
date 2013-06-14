#ifndef _KBD_SCANCODE_H_
#define _KBD_SCANCODE_H_

#define KBD_SCANCODE_SIZE 126

#include <diy-vt100/common.h>

struct __kbd_scancode
{
	/*
	 * 0 = do not exists
	 * 1 = character is affected by caps status
	 * other = call
	 */
	callback_t callback;
	
	/* 0:main, 1:replacement */
	uint8_t ch[2];
};

extern const struct __kbd_scancode kbd_scancode[KBD_SCANCODE_SIZE];

#endif
