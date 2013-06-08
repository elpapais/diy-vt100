#include <hardware/nokia1100.h>
#include <hardware/port2.h>
#include <hardware/flash.h>

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
nokia1100_clear()
{
	uint16_t i = NOKIA1100_SCREEN_LOOP_SIZE;
	
	nokia1100_showpixel_off();
	nokia1100_gotoyx(0,0);
	
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
	
	nokia1100_showpixel_on();
}

/* init */
void
nokia1100_init()
{
	/* initalization commands */
	nokia1100_chargepump_on();
	nokia1100_contrast(NOKIA1100_INIT_CONTRAST);
	nokia1100_power_on();
	nokia1100_clear();
	nokia1100_gotoy(0);
	nokia1100_gotox(0);
	
	if(flash_setting_read(SETTING_DECSCNM))
	{
		nokia1100_invertpixel_on();
	}
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
