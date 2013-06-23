#ifndef CQUEUE_H
#define CQUEUE_H

#include <diy-vt100/common.h>

#define CQUEUE_SIZE 32
#define CQUEUE_MOD 0x1F

typedef struct
{
	uint8_t count, start;
	uint8_t data[CQUEUE_SIZE];
}__attribute((packed)) cqueue_t;

void cqueue_push(cqueue_t *, const uint8_t);
uint8_t cqueue_pop(cqueue_t *);
void cqueue_overflow(cqueue_t *);

#endif
