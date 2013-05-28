#include <cqueue.h>

uint8_t cqueue_pop(struct __cqueue *queue)
{
	uint8_t data = queue->data[queue->start++];
	
	/* NOTE: using AND instead of %(modulo) */
	queue->start &= CQUEUE_MOD;
	
	queue->count--;
	
	return data;
}

void cqueue_push(struct __cqueue *queue, const uint8_t data)
{
	if(queue->count == CQUEUE_SIZE)
	{
		cqueue_overflow(queue);
	}
	
	/* NOTE: using AND instead of %(modulo) */
	uint8_t end = (queue->start + queue->count) & CQUEUE_MOD;
	
	queue->data[end] = data;
	queue->count++;
}

void cqueue_overflow(struct __cqueue *queue) 
{
	P1DIR |= BIT0;
	
	/* hang */
	while(1)
	{
		P1OUT ^= BIT0;
		__delay_cycles(600000);
	}
}
