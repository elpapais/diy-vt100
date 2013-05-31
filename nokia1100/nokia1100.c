#include <nokia1100.h>
#include <hardware/port2.h>

#define NOKIA1100_ONLY_CLKTRANSITION() \
		nokia1100_clk_low(); \
		nokia1100_clk_high()

#define NOKIA1100_CLKTRANSITION_WITHDATA(data, bit) \
		nokia1100_clk_low(); \
		if (data & bit) \
		{ \
			nokia1100_mosi_high(); \
		} \
		else \
		{ \
			nokia1100_mosi_low(); \
		} \
		 \
		nokia1100_clk_high()

void
nokia1100_clear()
{
	uint16_t i = NOKIA1100_SCREEN_LOOP_SIZE;
	
	nokia1100_showpixel_off();
	nokia1100_gotoyx(0,0);
	
	nokia1100_ss_low();
	
	/* send 0x00 in brust mode */
	while(i--)
	{
		nokia1100_mosi_high();
		
		NOKIA1100_ONLY_CLKTRANSITION();

		nokia1100_mosi_low();

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
	nokia1100_ss_high();
	
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
}

/* only used to send data in one go */
void
nokia1100_send_data(const uint8_t *data_array, const uint8_t size)
{
	uint8_t i;
	uint8_t data;
	
	nokia1100_clk_low();
	nokia1100_ss_low();
	
	for(i=0; i < size; i++)
	{
		data = data_array[i];
		nokia1100_mosi_high();
		nokia1100_clk_high();
		
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT7);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT6);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT5);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT4);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT3);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT2);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT1);
		NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT0);
		
		nokia1100_clk_low();
	}
	
	nokia1100_ss_high();
}

void
nokia1100_send_cmd(const uint8_t data)
{
	nokia1100_clk_low();
	nokia1100_ss_low();

	nokia1100_mosi_low();
	nokia1100_clk_high();

	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT7);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT6);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT5);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT4);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT3);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT2);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT1);
	NOKIA1100_CLKTRANSITION_WITHDATA(data, BIT0);
	
	nokia1100_clk_low();
	nokia1100_ss_high();
}
