#ifndef _SETTING_H_
#define _SETTING_H_

#include <common.h>

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
#define SETTING_DECCOM		__SETTING_VR(3)

/* private use of vt100 */
#define SETTING__UNSOLIC 		__SETTING_VR(4)
#define SETTING__CURSOR_STATE 	__SETTING_VR(5)
#define SETTING__ATTR_BOLD		__SETTING_VR(6)
#define SETTING__ATTR_UNDERLINE	__SETTING_VR(7)
#define SETTING__ATTR_INVERSE	__SETTING_VR(8)
#define SETTING__ATTR_BLINK		__SETTING_VR(9)

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

#define SETUP_ANSWERBACK_SIZE 20

/* saved in NVR */
struct __setting_nvr
{
	uint16_t bits;
	uint8_t speed;
	uint8_t brightness;
	uint8_t answerback[SETUP_ANSWERBACK_SIZE];
};

extern const struct __setting_nvr setting_nvr;

extern uint8_t setting_brightness;
extern uint8_t setting_speed;
extern uint16_t setting_tabs;

extern uint16_t setting_nvr_bits;
extern uint16_t setting_vr_bits;

#define __SETTING_REMOVE_RAM_INFO(no) (no & ~BIT7)
#define __SETTING_IS4NVR(no) (no & BIT7)
#define __SETTING_GENERATE_BITMASK(num) (1 << __SETTING_REMOVE_RAM_INFO(num))

#define __setting_select_mem(num, code_nvr, code_vr) \
	(__SETTING_IS4NVR(num) ? code_nvr : code_vr)

#define setting_flip(num) \
	__setting_select_mem(num, __setting_flip(setting_nvr_bits, num), \
								__setting_flip(setting_vr_bits, num))
	
#define setting_low(num) \
	__setting_select_mem(num, __setting_low(setting_nvr_bits, num), \
								__setting_low(setting_vr_bits, num))

#define setting_high(num) \
	__setting_select_mem(num, __setting_high(setting_nvr_bits, num), \
								__setting_high(setting_vr_bits, num))

#define setting_read(num) \
	(!!(__setting_select_mem(num, __setting_read(setting_nvr_bits, num), \
								__setting_read(setting_vr_bits, num))))

#define __setting_read(var, no) (var & __SETTING_GENERATE_BITMASK(no))
#define __setting_flip(var, no) (var ^= __SETTING_GENERATE_BITMASK(no))
#define __setting_high(var, no) (var |= __SETTING_GENERATE_BITMASK(no))
#define __setting_low(var, no) (var &= ~__SETTING_GENERATE_BITMASK(no))

void setting_load();
void setting_save();

#endif
