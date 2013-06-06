#ifndef _VT100_MISC_H_
#define _VT100_MISC_H_

#include <common.h>

void vt100_DECKPAM();
void vt100_RIS();
void vt100_init();
void vt100_DECSCNM();
void vt100_ENQ();

bool_t __is_vt100_malfunctioning();

void vt100_DECTST();

#endif
