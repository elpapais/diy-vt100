#ifndef PARAM_H
#define PARAM_H

#include <diy-vt100/common.h>

#define PARAM_QUEUE_SIZE 8
#define PARAM_DELIMITER ';'

typedef struct
{
	uint8_t count;
	uint8_t data[PARAM_QUEUE_SIZE];
	uint8_t pass;
} __attribute((packed)) param_t;

extern param_t param;

void param_add();
void param_default(int8_t pcount, uint8_t pdefault);
#endif
