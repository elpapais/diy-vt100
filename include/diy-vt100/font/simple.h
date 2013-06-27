#ifndef FONT_SIMPLE_H
#define FONT_SIMPLE_H

#include <diy-vt100/common.h>

extern const uint8_t font_simple_table[256][6];
#define font_simple_get(num, part) (font_simple_table[num][part])

#endif
