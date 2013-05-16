#ifndef _VT100_TAB_H_
#define _VT100_TAB_H_

#include <vt100/extern.h>
#include <vt100/screen.h>

void vt100_tabulation_clear();
void vt100_set_horizontal_tabulation();
void vt100_goto_next_tab();

#endif
