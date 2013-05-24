#include <nokia1100.h>

void
nokia1100_clear()
{	
	register uint16_t i = NOKIA1100_SCREEN_LOOP_SIZE;
	
	nokia1100_showpixel_off();
	nokia1100_gotoyx(0,0);
	
	NOKIA1100_POUT &= ~NOKIA1100_SS;
	
	/* send 0x00 in brust mode */
	while(i--)
	{
#define NOKIA1100_CLOCK_TRANSITION() NOKIA1100_POUT &= ~NOKIA1100_CLK; \
									 NOKIA1100_POUT |= NOKIA1100_CLK

		NOKIA1100_POUT |= NOKIA1100_MOSI;
		
		NOKIA1100_CLOCK_TRANSITION();

		NOKIA1100_POUT &= ~NOKIA1100_MOSI;

		NOKIA1100_CLOCK_TRANSITION();
		NOKIA1100_CLOCK_TRANSITION();
		NOKIA1100_CLOCK_TRANSITION();
		NOKIA1100_CLOCK_TRANSITION();
		NOKIA1100_CLOCK_TRANSITION();
		NOKIA1100_CLOCK_TRANSITION();
		NOKIA1100_CLOCK_TRANSITION();
		NOKIA1100_CLOCK_TRANSITION();
	}
	
	/* Disable display LCD */
	NOKIA1100_POUT |= NOKIA1100_SS;
	
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

/* only used to send data */
void
nokia1100_send_data_brustmode(const uint8_t send[], const uint16_t size)
{	
	uint16_t i;
	uint8_t count;
	uint8_t data;
	
	NOKIA1100_POUT &= ~NOKIA1100_CLK;
	NOKIA1100_POUT &= ~NOKIA1100_SS;
	
	for(i=0; i < size; i++)
	{
		count=8;
		data = send[i];
		NOKIA1100_POUT |= NOKIA1100_MOSI;
		NOKIA1100_POUT |= NOKIA1100_CLK;
	
		while(count--)
		{
			NOKIA1100_POUT &= ~NOKIA1100_CLK;
		
			if (data & 0x01)
			{
				NOKIA1100_POUT |= NOKIA1100_MOSI;
			}
			else
			{
				NOKIA1100_POUT &= ~NOKIA1100_MOSI;
			}
			
			NOKIA1100_POUT |= NOKIA1100_CLK;
		
			data >>= 1;
		}
		
		NOKIA1100_POUT &= ~NOKIA1100_CLK;
	}
	
	/* Disable display LCD */
	NOKIA1100_POUT |= NOKIA1100_SS;
}

void
nokia1100_send(uint16_t send)
{
	uint8_t count=9;
	
	NOKIA1100_POUT &= ~NOKIA1100_CLK;
	NOKIA1100_POUT &= ~NOKIA1100_SS;

	/* send data */
	while (count--)
	{
		NOKIA1100_POUT &= ~NOKIA1100_CLK;
		
		if (send & 0x0100)
		{
			NOKIA1100_POUT |= NOKIA1100_MOSI;
		}
		else
		{
			NOKIA1100_POUT &= ~NOKIA1100_MOSI;
		}
		
		NOKIA1100_POUT |= NOKIA1100_CLK;
		
		send <<= 1;
	}
   
	/* Disable display LCD */
	NOKIA1100_POUT |= NOKIA1100_SS;
}
