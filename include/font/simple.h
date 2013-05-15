#ifndef _VT100_FONT_H_
#define _VT100_FONT_H_

#include <common.h>


#define EXTASCII_BOX_TOPLEFT 0xDA
#define EXTASCII_BOX_TOPRIGHT 0xBF
#define EXTASCII_BOX_BOTLEFT 0xC0
#define EXTASCII_BOX_BOTRIGHT 0xD9
#define EXTASCII_BOX_HORZ 0xC4
#define EXTASCII_BOX_VERT 0xB3

extern const uint8_t font_simple_table[256][6];
uint8_t font_simple_get(uint8_t,uint8_t);

#endif
