#ifndef VT100_MISC_H
#define VT100_MISC_H

#include <diy-vt100/common.h>

void vt100_refresh_connect_mode(void);

void vt100_DECKPAM(void);
void vt100_RIS(void);
void vt100_init(void);
void vt100_DECSCNM(void);
void vt100_ENQ(void);

void vt100_setting_low(void);
void vt100_setting_high(void);

void vt100_DECTST(void);
void vt100_DECLL(void);

void vt100_XOFF(void);
void vt100_XON(void);

#endif
