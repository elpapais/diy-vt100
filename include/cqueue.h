#ifndef _CQUEUE_H_
#define _CQUEUE_H_

#include <common.h>

#define CQUEUE_SIZE 32
#define CQUEUE_MOD 0x1F

struct __cqueue
{
	uint8_t count, start;
	uint8_t data[CQUEUE_SIZE];
};

void cqueue_push(struct __cqueue *, const uint8_t);
uint8_t cqueue_pop(struct __cqueue *);
void cqueue_overflow(struct __cqueue *queue);

#endif
