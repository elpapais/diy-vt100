#include <diy-vt100/hardware/ic_74xx595.h>
#include <diy-vt100/hardware/port1.h>

uint8_t ic_74xx595;

#define IC_74XX595_SEND_BIT(bit) \
	port1_low(IC_74XX595_SHCP); \
	if(__read(ic_74xx595, bit)) \
	{ \
		port1_high(IC_74XX595_DATA); \
	} \
	else \
	{ \
		port1_low(IC_74XX595_DATA); \
	} \
	port1_high(IC_74XX595_SHCP)

void ic_74xx595_refresh()
{
	IC_74XX595_SEND_BIT(IC_74xx595_PIN7);
	IC_74XX595_SEND_BIT(IC_74xx595_PIN6);
	IC_74XX595_SEND_BIT(IC_74xx595_PIN5);
	IC_74XX595_SEND_BIT(IC_74xx595_PIN4);
	IC_74XX595_SEND_BIT(IC_74xx595_PIN3);
	IC_74XX595_SEND_BIT(IC_74xx595_PIN2);
	IC_74XX595_SEND_BIT(IC_74xx595_PIN1);
	IC_74XX595_SEND_BIT(IC_74xx595_PIN0);
	
	port1_high(IC_74XX595_STCP);
	port1_low(IC_74XX595_SHCP | IC_74XX595_DATA | IC_74XX595_STCP);
}
