#include <hardware/nokia1100.h>
#include <hardware/ic_74xx595.h>
#include <vt100/bell.h>

void
vt100_audio_bell()
{
	ic_74xx595_high(VT100_BELL);
	ic_74xx595_refresh();
	ic_74xx595_low(VT100_BELL);
	ic_74xx595_refresh();
}

void
vt100_visual_bell()
{
	nokia1100_allpixel_on();
	__delay_cycles(10000);
	nokia1100_allpixel_off();
}

void vt100_BEL()
{
	vt100_audio_bell();
}
