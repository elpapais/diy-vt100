#ifndef PARAM_H
#define PARAM_H

#include <diy-vt100/common.h>

#define PARAM_QUEUE_SIZE 8
#define PARAM_DELIMITER ';'

typedef struct
{
	volatile uint8_t count;
	volatile uint8_t data[PARAM_QUEUE_SIZE];
} __attribute((packed)) param_t;

extern param_t param;

void param_add(const uint8_t);
void param_default(const int8_t pcount, const uint8_t pdefault);
#endif
