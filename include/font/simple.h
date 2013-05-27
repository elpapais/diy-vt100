#ifndef _VT100_FONT_H_
#define _VT100_FONT_H_

#include <common.h>

extern const uint8_t font_simple_table[256][6];
uint8_t font_simple_get(uint8_t,uint8_t);

#endif
