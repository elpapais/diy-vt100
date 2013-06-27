#include <diy-vt100/hardware/cqueue.h>

uint8_t cqueue_pop(cqueue_t *queue)
{
	uint8_t data = queue->data[queue->start++];
	
	/* NOTE: using AND instead of %(modulo) */
	queue->start &= CQUEUE_MOD;
	
	queue->count--;
	
	return data;
}

void cqueue_push(cqueue_t *queue, const uint8_t data)
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

void cqueue_overflow(cqueue_t *queue) 
{
	P1DIR |= BIT0;
	
	/* hang */
	while(1)
	{
		P1OUT ^= BIT0;
		__delay_cycles(6553500);
	}
}

void cqueue_underflow(cqueue_t *queue)
{

}
