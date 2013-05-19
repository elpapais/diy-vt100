#include <nokia1100.h>

void
nokia1100_clear()
{	
	uint16_t i;
	
	nokia1100_allpixel_off();
	
	nokia1100_gotoyx(0,0);
	
	for( i = 0; i < NOKIA1100_SCREEN_LOOP_SIZE; i++)
	{
		nokia1100_send_data(0x00);
	}
	
	nokia1100_allpixel_off();
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
