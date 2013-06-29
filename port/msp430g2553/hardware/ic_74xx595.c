#include <diy-vt100/msp430g2553/ic_74xx595.h>
#include <diy-vt100/msp430g2553/port1.h>

ic_74xx595_t ic_74xx595;

#define IC_74XX595_SEND_BIT(bit) \
	port1_low(IC_74XX595_SHCP); \
	if(bit) \
	{ \
		port1_high(IC_74XX595_DATA); \
	} \
	else \
	{ \
		port1_low(IC_74XX595_DATA); \
	} \
	port1_high(IC_74XX595_SHCP)

void ic_74xx595_refresh(void)
{
	IC_74XX595_SEND_BIT(ic_74xx595.led_prog4);
	IC_74XX595_SEND_BIT(ic_74xx595.led_prog3);
	IC_74XX595_SEND_BIT(ic_74xx595.led_prog2);
	IC_74XX595_SEND_BIT(ic_74xx595.led_prog1);
	IC_74XX595_SEND_BIT(ic_74xx595.led_kbdlock);
	IC_74XX595_SEND_BIT(ic_74xx595.led_offline);
	IC_74XX595_SEND_BIT(ic_74xx595.led_online);
	IC_74XX595_SEND_BIT(ic_74xx595.buzzer);
	
	port1_high(IC_74XX595_STCP);
	port1_low(IC_74XX595_SHCP | IC_74XX595_DATA | IC_74XX595_STCP);
}
