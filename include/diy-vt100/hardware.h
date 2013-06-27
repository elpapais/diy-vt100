#ifndef HARDWARE_H
#define HARDWARE_H

#include <diy-vt100/common.h>

void hardware_init(void);
void hardware_reset(void);
void hardware_loop(void);
bool_t hardware_malfunctioning(void);

#endif
