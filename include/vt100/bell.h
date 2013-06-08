#ifndef _VT100_BELL_H_
#define _VT100_BELL_H_

#include <common.h>
#include <hardware/ic_74xx595.h>

#define vt100_bell_init() ic_74xx595_low(VT100_BELL)

void vt100_audio_bell();
void vt100_visual_bell();
void vt100_BEL();

#endif
