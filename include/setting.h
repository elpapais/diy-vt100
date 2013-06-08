#ifndef _SETTING_H_
#define _SETTING_H_

#include <common.h>
#include <hardware/flash.h>

#define SETTING_ANSWERBACK_SIZE 20

struct __setting
{
	uint8_t vr_bits;
	uint16_t nvr_bits;
	uint8_t brightness;
	uint8_t speed;
	uint16_t tabs;
	uint8_t answerback[SETTING_ANSWERBACK_SIZE];
};

extern struct __setting setting;

/* note: (FALSE|TRUE)
 * ONLINE: 	(online mode|offline mode)
 * MODE: 	(vt52|ansi)
 * AUTOX: 	auto XON & XOFF (OFF|ON)
 * BPS:		bits per character(7|8)
 * DECCOLM:	character per line(80|130)
 * CURSOR: 	cursor (block|underline)
 * SHIFTED:	#, EURO selection (#|EURO)
 * POWER: 	(60Hz|50Hz)
 * SCREEN: 	(DARK|LIGHT)
 */

#define __setting_nvr(no) 	(no | BIT7)
#define __setting_vr(no) 	(no & (~BIT7))

#define SETTING_DECKPAM		__setting_vr(0)
#define SETTING_DECCKM		__setting_vr(2)
#define SETTING_DECGON		__setting_vr(1)
#define SETTING_DECOM		__setting_vr(3)

/* private use of vt100 */
#define SETTING__UNSOLIC 		__setting_vr(4)
#define SETTING__CURSOR_STATE 	__setting_vr(5)
#define SETTING__ATTR_BOLD		__setting_vr(6)
#define SETTING__ATTR_UNDERLINE	__setting_vr(7)
#define SETTING__ATTR_INVERSE	__setting_vr(8)
#define SETTING__ATTR_BLINK		__setting_vr(9)
#define SETTING__LOCAL			__setting_vr(10)

#define SETTING_DECANM 		__setting_nvr(0)
#define SETTING_DECARM 		__setting_nvr(1)
#define SETTING_AUTOX 		__setting_nvr(2)
#define SETTING_BPC 		__setting_nvr(3)
#define SETTING_DECCOLM		__setting_nvr(4)
#define SETTING_CURSOR		__setting_nvr(5)
#define SETTING_DECINLM		__setting_nvr(6)
#define SETTING_LNM			__setting_nvr(7)
#define SETTING_KEYCLICK	__setting_nvr(8)
#define SETTING_MARGINBELL	__setting_nvr(9)
#define SETTING_PARITY		__setting_nvr(10)
#define SETTING_PARITYSENSE	__setting_nvr(11)
#define SETTING_DECSCNM		__setting_nvr(12)
#define SETTING_DECSCLM		__setting_nvr(13)
#define SETTING_DECAWM		__setting_nvr(14)
#define SETTING_SHIFTED		__setting_nvr(15)

#define __setting_get_actual_bitmask(num) __bitmask(num & ~BIT7) /* remove BIT7(for NVR or not) */
#define __setting_read(var, num) __read(var, __setting_get_actual_bitmask(num))
#define __setting_flip(var, num) __flip(var, __setting_get_actual_bitmask(num))
#define __setting_high(var, num) __high(var, __setting_get_actual_bitmask(num))
#define __setting_low(var, num)  __low(var, __setting_get_actual_bitmask(num))

#define __setting_select_mem(num, code_nvr, code_vr) \
	(__read(num, BIT7) /* is NVR */ ? code_nvr : code_vr)

#define setting_flip(num) \
	__setting_select_mem(num, __setting_flip(setting.nvr_bits, num), \
								__setting_flip(setting.vr_bits, num))
	
#define setting_low(num) \
	__setting_select_mem(num, __setting_low(setting.nvr_bits, num), \
								__setting_low(setting.vr_bits, num))

#define setting_high(num) \
	__setting_select_mem(num, __setting_high(setting.nvr_bits, num), \
								__setting_high(setting.vr_bits, num))

#define setting_read(num) \
	(!!(__setting_select_mem(num, __setting_read(setting.nvr_bits, num), \
								__setting_read(setting.vr_bits, num))))

#define setting_tab_high(pos) 	__high(setting.tabs, __bitmask(pos))
#define setting_tab_low(pos) 	__low(setting.tabs, __bitmask(pos))
#define setting_tab_read(pos) 	__read(setting.tabs, __bitmask(pos))
#define setting_tab_flip(pos) 	__flip(setting.tabs, __bitmask(pos))
#define setting_tab_clear() 	__clear(setting.tabs)

#define setting_save() flash_store()
#define setting_load() flash_load()
#define setting_init() flash_load()

#endif
