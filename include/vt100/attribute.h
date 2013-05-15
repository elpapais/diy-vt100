#ifndef _VT100_ATTRIBUTE_H_
#define _VT100_ATTRIBUTE_H_

#include <vt100/extern.h>
#include <vt100/screen.h>

void vt100_select_attribute();
void vt100_set_doublewidth();
void vt100_set_doubleheight_bottomhalf();
void vt100_set_doubleheight_tophalf();

#endif
