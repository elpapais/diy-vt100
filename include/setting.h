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

#define __SETTING_NVR(no) 	(no | BIT7)
#define __SETTING_VR(no) 	(no & (~BIT7))

#define SETTING_DECKPAM		__SETTING_VR(0)
#define SETTING_DECCKM		__SETTING_VR(2)
#define SETTING_DECGON		__SETTING_VR(1)
#define SETTING_DECOM		__SETTING_VR(3)

/* private use of vt100 */
#define SETTING__UNSOLIC 		__SETTING_VR(4)
#define SETTING__CURSOR_STATE 	__SETTING_VR(5)
#define SETTING__ATTR_BOLD		__SETTING_VR(6)
#define SETTING__ATTR_UNDERLINE	__SETTING_VR(7)
#define SETTING__ATTR_INVERSE	__SETTING_VR(8)
#define SETTING__ATTR_BLINK		__SETTING_VR(9)
#define SETTING__LOCAL			__SETTING_VR(10)

#define SETTING_DECANM 		__SETTING_NVR(0)
#define SETTING_DECARM 		__SETTING_NVR(1)
#define SETTING_AUTOX 		__SETTING_NVR(2)
#define SETTING_BPC 		__SETTING_NVR(3)
#define SETTING_DECCOLM		__SETTING_NVR(4)
#define SETTING_CURSOR		__SETTING_NVR(5)
#define SETTING_DECINLM		__SETTING_NVR(6)
#define SETTING_LNM			__SETTING_NVR(7)
#define SETTING_KEYCLICK	__SETTING_NVR(8)
#define SETTING_MARGINBELL	__SETTING_NVR(9)
#define SETTING_PARITY		__SETTING_NVR(10)
#define SETTING_PARITYSENSE	__SETTING_NVR(11)
#define SETTING_DECSCNM		__SETTING_NVR(12)
#define SETTING_DECSCLM		__SETTING_NVR(13)
#define SETTING_DECAWM		__SETTING_NVR(14)
#define SETTING_SHIFTED		__SETTING_NVR(15)

#define __SETTING_REMOVE_RAM_INFO(no) (no & ~BIT7)
#define __SETTING_IS4NVR(no) (no & BIT7)
#define __SETTING_GENERATE_BITMASK(num) (1 << __SETTING_REMOVE_RAM_INFO(num))

#define __setting_select_mem(num, code_nvr, code_vr) \
	(__SETTING_IS4NVR(num) ? code_nvr : code_vr)

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

#define __setting_read(var, no) (var & __SETTING_GENERATE_BITMASK(no))
#define __setting_flip(var, no) (var ^= __SETTING_GENERATE_BITMASK(no))
#define __setting_high(var, no) (var |= __SETTING_GENERATE_BITMASK(no))
#define __setting_low(var, no) (var &= ~__SETTING_GENERATE_BITMASK(no))

#define setting_tab_high(pos) (setting.tabs |= (1 << (pos)))
#define setting_tab_low(pos) (setting.tabs &= ~(1 << (pos)))
#define setting_tab_read(pos) (setting.tabs & (1 << (pos)))
#define setting_tab_flip(pos) (setting.tabs ^= (1 << (pos)))
#define setting_tab_clearall() (setting.tabs = 0)

#define setting_save() flash_setting_write()
#define setting_load() flash_setting_read()
#define setting_init() flash_setting_read()

#endif
