#ifndef _VT100_SCREEN_H_
#define _VT100_SCREEN_H_

#include <nokia1100.h>
#include <font/simple.h>
#include <vt100/buffer.h>
#include <common.h>


void vt100_screen_refresh();
void vt100_screen_clear();
void vt100_screen_printchar(row_t i,col_t j,bool_t has_cursor);

#endif
