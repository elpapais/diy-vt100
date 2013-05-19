#include <cqueue.h>

uint8_t cqueue_pop(struct __cqueue *queue)
{
	queue->count--;
	
	return queue->data[queue->start++];
}

void cqueue_push(struct __cqueue *queue, const uint8_t data)
{
	queue->data[queue->end++] = data;
	
	if(++queue->count == CQUEUE_SIZE)
	{
		cqueue_overflow(queue);
	}
}

void cqueue_overflow(struct __cqueue *queue) 
{
	P1DIR |= BIT0;
	
	/* hang */
	while(1)
	{
		P1OUT ^= BIT0;
		__delay_cycles(10000);
	}
}
