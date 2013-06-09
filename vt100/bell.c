#include <hardware/buzzer.h>
#include <vt100/bell.h>

void vt100_BEL()
{
	buzzer_long();
}
