#ifndef _VT100_PARAM_H_
#define _VT100_PARAM_H_

#include <common.h>

#define VT100_PARAM_QUEUE_SIZE 8
#define VT100_PARAM_DELIMITER ';'

struct __vt100_param
{
	uint8_t count;
	uint8_t data[VT100_PARAM_QUEUE_SIZE];
	uint8_t pass;
};

extern struct __vt100_param vt100_param;

void vt100_param_add();
void vt100_param_default(uint8_t pcount, uint8_t pdefault);
#endif
