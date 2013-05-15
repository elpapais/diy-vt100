#ifndef _VT100_SCREEN_H_
#define _VT100_SCREEN_H_

#include <nokia1100.h>

#define VT100_WIDTH NOKIA1100_COLOUMN
#define VT100_HEIGHT NOKIA1100_ROW

#include <font/simple.h>
#include <vt100/type.h>
#include <vt100/extern.h>
#include <common.h>

void vt100_refresh();
void vt100_clear();
void vt100_print_char(row_t i, col_t j, bool_t has_cursor);

#endif
