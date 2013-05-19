#include <hardware/port1.h>

void port1_init()
{
	/* output port */
	NOKIA1100_PDIR |= NOKIA1100_SS | NOKIA1100_CLK | NOKIA1100_MOSI;
	NOKIA1100_POUT |= NOKIA1100_SS;
	
	/* init code for nokia1100 */
	nokia1100_init();
}
