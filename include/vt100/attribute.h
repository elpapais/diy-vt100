#ifndef _VT100_ATTRIBUTE_H_
#define _VT100_ATTRIBUTE_H_

#include <vt100/buffer.h>
#include <vt100/misc.h>

void vt100_attribute_select();
void vt100_double_width();
void vt100_double_height_bottomhalf();
void vt100_double_height_tophalf();

#endif
