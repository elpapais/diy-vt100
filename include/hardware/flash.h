#ifndef _HW_FLASH_H_
#define _HW_FLASH_H_

#include <common.h>
#include <setting.h>

extern const struct __setting flash_setting;

/*
 * flash @ 4MHz/13 = 307692Hz
 * clocked from SMCLK
 */
#define FN_12 (FN2|FN3)
#define flash_init() (FCTL2 = FWKEY + FSSEL_2 + FN_12)


#define flash_setting_read(num) \
	__setting_select_mem(num, __setting_read(flash_setting.nvr_bits, num), \
								__setting_read(setting.vr_bits, num))
								
#define flash_setting_ishigh(num) \
	__setting_select_mem(num, __setting_ishigh(flash_setting.nvr_bits, num), \
								__setting_ishigh(setting.vr_bits, num))
								
#define flash_setting_islow(num) \
	__setting_select_mem(num, __setting_islow(flash_setting.nvr_bits, num), \
								__setting_islow(setting.vr_bits, num))

#define flash_setting_tab_read(pos) \
	__read(flash_setting.tabs, __bitmask(pos))

void flash_store();
void flash_load();

#endif
