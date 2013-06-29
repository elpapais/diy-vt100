#include <diy-vt100/screen.h>
#include <diy-vt100/msp430g2553/screen/nokia1100.h>
#include <diy-vt100/msp430g2553/port2.h>

#define NOKIA1100_ONLY_CLKTRANSITION() \
		port2_low(NOKIA1100_CLK); \
		port2_high(NOKIA1100_CLK)

#define NOKIA1100_CLKTRANSITION_WITHDATA(data, bit) \
		port2_low(NOKIA1100_CLK); \
		if (data & bit) \
		{ \
			port2_high(NOKIA1100_MOSI); \
		} \
		else \
		{ \
			port2_low(NOKIA1100_MOSI); \
		} \
		 \
		port2_high(NOKIA1100_CLK)

void
nokia1100_full_clear(void)
{
	uint16_t i = 864;
	
	port2_low(NOKIA1100_SS);
	
	/* send 0x00 in brust mode */
	while(i--)
	{
		port2_high(NOKIA1100_MOSI);
		
		NOKIA1100_ONLY_CLKTRANSITION();

		port2_low(NOKIA1100_MOSI);

		NOKIA1100_ONLY_CLKTRANSITION();
		NOKIA1100_ONLY_CLKTRANSITION();
		NOKIA1100_ONLY_CLKTRANSITION();
		NOKIA1100_ONLY_CLKTRANSITION();
		NOKIA1100_ONLY_CLKTRANSITION();
		NOKIA1100_ONLY_CLKTRANSITION();
		NOKIA1100_ONLY_CLKTRANSITION();
		NOKIA1100_ONLY_CLKTRANSITION();
	}
	
	/* Disable display LCD */
	port2_high(NOKIA1100_SS);
}

/* only used to send data in one go */
void
nokia1100_send_data(const uint8_t *data_array, const uint8_t size)
{
	uint8_t i;
	uint8_t data;
	
	//port2_low(NOKIA1100_CLK | NOKIA1100_SS);
	port2_low(NOKIA1100_CLK);
	port2_low(NOKIA1100_SS);
	
	for(i=0; i < size; i++)
	{
		data = data_array[i];
		port2_high(NOKIA1100_MOSI);
		port2_high(NOKIA1100_CLK);
		
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT7);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT6);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT5);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT4);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT3);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT2);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT1);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT0);
		
		port2_low(NOKIA1100_CLK);
	}
	
	port2_high(NOKIA1100_SS);
}

void
nokia1100_send_cmd(const uint8_t data)
{
	port2_low(NOKIA1100_CLK);
	port2_low(NOKIA1100_SS);

	port2_low(NOKIA1100_MOSI);
	port2_high(NOKIA1100_CLK);

	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT7);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT6);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT5);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT4);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT3);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT2);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT1);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT0);
	
	port2_low(NOKIA1100_CLK);
	port2_high(NOKIA1100_SS);
}
