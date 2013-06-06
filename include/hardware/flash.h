#ifndef _FLASH_H_
#define _FLASH_H_

#include <common.h>

/*
 * flash @ 4MHz/13 = 307692Hz
 * clocked from SMCLK
 */
#define FN_12 (FN2|FN3)
#define flash_init() (FCTL2 = FWKEY + FSSEL_2 + FN_12)

void flash_setting_write();
void flash_setting_read();

#endif
