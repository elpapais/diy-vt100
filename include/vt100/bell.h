#ifndef _VT100_BELL_H_
#define _VT100_BELL_H_

#include <vt100/pin.h>
#include <nokia1100.h>
#include <common.h>

void vt100_bell_init();
void vt100_bell();
void vt100_audio_bell();
void vt100_visual_bell();

#define VT100_BELL_AUDIO_DELAY() __delay_cycles(5000)
#define VT100_BELL_VISUAL_DELAY() __delay_cycles(5000)

#endif
