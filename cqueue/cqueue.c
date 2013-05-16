#include <cqueue.h>

uint8_t cqueue_pop(struct __cqueue *queue)
{
	uint8_t data = queue->data[queue->start++];
	
	queue->start |= CQUEUE_MOD;
	
	queue->count--;
	
	return data;
}

void cqueue_push(struct __cqueue *queue, const uint8_t data)
{
	register uint8_t end = (queue->start + queue->count) & CQUEUE_MOD;
	
	queue->data[end] = data;
	
	if(queue->count == CQUEUE_SIZE)
	{
		cqueue_overflow(queue);
	}
	else
	{
		queue->count++;
	}
}

