#ifndef _CQUEUE_H_
#define _CQUEUE_H_

#define CQUEUE_SIZE 32
#define CQUEUE_MOD CQUEUE_SIZE

#include <common.h>

struct __cqueue
{
	uint8_t count, start;
	uint8_t data[CQUEUE_SIZE];
};

void cqueue_push(struct __cqueue *, const uint8_t);
uint8_t cqueue_pop(struct __cqueue *);
#define cqueue_count(queue) (queue.count)
#define cqueue_overflow(queue) /* do nothing for now */

#endif
