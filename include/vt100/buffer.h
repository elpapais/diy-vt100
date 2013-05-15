#ifndef _VT100_BUFFER_H_
#define _VT100_BUFFER_H_

#include <common.h>
#include <vt100/extern.h>

void vt100_buffer_putchar();
void vt100_buffer_newrow();
void vt100_buffer_shiftup();
void vt100_buffer_shiftdown();
void vt100_buffer_clear_char(const row_t i, const col_t j);
void vt100_fill_all_E();
void vt100_erase();

#endif
