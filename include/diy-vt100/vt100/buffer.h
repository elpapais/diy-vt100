#ifndef VT100_CHAR_H
#define VT100_CHAR_H

#include <diy-vt100/common.h>

/* when parity error occurs , hardware will send 
 * place a checkerboard character ascii(176) */
void vt100_putch(void);

void vt100_DECALN(void);

void vt100_LF(void);
void vt100_NEL(void);
void vt100_CR(void);

void vt100_ED(void);
void vt100_EL(void);

#endif
