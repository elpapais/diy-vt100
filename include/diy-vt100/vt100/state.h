#ifndef _VT100_STATE_H_
#define _VT100_STATE_H_

#include <diy-vt100/state-machine.h>

extern const struct __state vt100_state_C0[];
extern const struct __state vt100_state_C1[];
extern const struct __state vt100_state_hash[];
extern const struct __state vt100_state_open_smallbracket[];
extern const struct __state vt100_state_opensquarebracket[];
extern const struct __state vt100_state_close_smallbracket[];

void vt100_state_worker();

#endif
