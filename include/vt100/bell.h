#ifndef _VT100_BELL_H_
#define _VT100_BELL_H_

#include <common.h>

#define VT100_BELL_PDIR P2DIR
#define VT100_BELL_POUT P2OUT
#define VT100_BELL_PIN BIT5

void vt100_bell_init();
void vt100_audio_bell();
void vt100_visual_bell();

#endif
