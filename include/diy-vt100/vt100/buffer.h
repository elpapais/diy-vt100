#ifndef VT100_CHAR_H
#define VT100_CHAR_H

#include <diy-vt100/common.h>

void vt100_putchar();

void vt100_DECALN();

void vt100_LF();
void vt100_NEL();
void vt100_CR();

void vt100_ED();
void vt100_EL();

#endif
