#ifndef _VT100_SETTING_H_
#define _VT100_SETTING_H_

#include <common.h>

void vt100_setting_save(void *src, uint8_t size);
void vt100_setting_load(void *dest, uint8_t size);

#endif
