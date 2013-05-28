#ifndef _VT100_FONT_H_
#define _VT100_FONT_H_

#include <common.h>

extern const uint8_t font_simple_table[256][6];
#define font_simple_get(num, part) (font_simple_table[num][part])

#endif
