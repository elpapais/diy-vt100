#ifndef _CQUEUE_H_
#define _CQUEUE_H_

#include <common.h>

#define CQUEUE_SIZE 32

struct __cqueue
{
	/* limit till 2^5 = 32 */
	uint8_t count, start;
	uint8_t data[CQUEUE_SIZE];
};

void cqueue_push(struct __cqueue *, const uint8_t);
uint8_t cqueue_pop(struct __cqueue *);
#define cqueue_count(queue) (queue.count)
void cqueue_overflow(struct __cqueue *queue);

#endif
