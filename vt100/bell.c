#include <vt100/bell.h>

void
vt100_bell_init()
{
	VT100_BELL_PDIR |= VT100_BELL_PIN;
	VT100_BELL_POUT &= ~VT100_BELL_PIN;
}

void
vt100_audio_bell()
{
	/* TODO: make proper frequency(currently only used as dumb value) */
	VT100_BELL_POUT |= VT100_BELL_PIN;
	VT100_BELL_AUDIO_DELAY();
	VT100_BELL_POUT &= ~VT100_BELL_PIN;
}

void
vt100_visual_bell()
{
	nokia1100_allpixel_on();
	VT100_BELL_VISUAL_DELAY();
	nokia1100_allpixel_off();
}

void
vt100_bell()
{
	vt100_audio_bell();
}
