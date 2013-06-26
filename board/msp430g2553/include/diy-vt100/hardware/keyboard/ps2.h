#ifndef KBD_H
#define KBD_H

#include <diy-vt100/common.h>
#include <diy-vt100/hardware/cqueue.h>

extern cqueue_t ps2kbd;
void ps2kbd_decode(uint8_t);

#endif
