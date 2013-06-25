#ifndef HW_SETTING_H
#define HW_SETTING_H

#include <diy-vt100/setting.h>

/* === parmanent setting === */
extern const setting_t parm_setting;

#define parm_setting_tab_islow(pos) __islow(parm_setting.tabs, __bitmask(pos))
#define parm_setting_tab_ishigh(pos) __ishigh(parm_setting.tabs, __bitmask(pos))

#endif
