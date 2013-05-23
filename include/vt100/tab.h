#ifndef _VT100_TAB_H_
#define _VT100_TAB_H_

#include <vt100/buffer.h>
#include <vt100/cursor.h>

void vt100_tabulation_clear();
void vt100_tabulation_set();
void vt100_tabulation_goto_next();

#endif
