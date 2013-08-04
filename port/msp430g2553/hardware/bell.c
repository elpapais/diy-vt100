#include <diy-vt100/bell.h>
#include <stdint.h>

void timer0_A3_start(const uint16_t delay);

void bell_short(void)
{
	timer0_A3_start(0x2000);
}

void bell_long(void)
{
	timer0_A3_start(0xFFFF);
}
