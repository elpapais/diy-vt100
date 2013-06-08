#ifndef _VT100_BELL_H_
#define _VT100_BELL_H_

#include <hardware/buzzer.h>

#define vt100_bell_init() buzzer_off()

void vt100_BEL();

#endif
