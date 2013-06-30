#ifndef SETTING_H
#define SETTING_H

#include <diy-vt100/common.h>
#include <diy-vt100/screen.h>

#define answerback_size 20

/* ONLINE: 	(online mode|offline mode)
 * MODE: 	(vt52|ansi)
 * AUTOX: 	auto XON & XOFF (OFF|ON)
 * BPS:		bits per character(7|8)
 * DECCOLM:	character per line(80|130)
 * CURSOR: 	cursor (block|underline)
 * SHIFTED:	#, EURO selection (#|EURO)
 * POWER: 	(60Hz|50Hz)
 * SCREEN: 	(DARK|LIGHT)
 */

#define TABS_SIZE ((SCREEN_COL/8) + ((SCREEN_COL/8.0) - (SCREEN_COL/8)) > 0 ? 1 : 0)

typedef struct
{
	struct
	{
		/* DEC PRIV - VR */
		uint8_t DECKPAM:1;
		uint8_t DECCKM:1;
		uint8_t DECGON:1;
		uint8_t DECCOM:1;

		/* VT100 PRIVATE - VR */
		uint8_t UNSOLIC:1;
		uint8_t LOCAL:1;
		uint8_t SETUP_TYPE:1;
		uint8_t SETUP_SHOW:1;

		/* KEYBOARD - VR */
		uint8_t KBD_SHIFT:1;
		uint8_t KBD_CTRL:1;
		uint8_t KBD_CAPS:1;

		/* HW - PRIVATE - NA */
		uint8_t HW_PRIV0:1;
		uint8_t HW_PRIV1:1;
		uint8_t HW_PRIV2:1;

		/* XON / XOFF */
		uint8_t XOFF_SEND:1; 		/* is XOFF send */
		uint8_t XOFF_SCROLL:1; 		/* send XOFF by user */
		uint8_t XOFFED:1;			/* XOFFed by computer */

		/* DEC PRIV - NVR */
		uint8_t DECANM:1;
		uint8_t DECARM:1;
		uint8_t AUTOX:1;
		uint8_t BPC:1;
		uint8_t DECCOLM:1;
		uint8_t CURSOR:1;
		uint8_t DECINLM:1;
		uint8_t LNM:1;
		uint8_t KEYCLICK:1;
		uint8_t MARGINBELL:1;
		uint8_t PARITY:1;
		uint8_t PARITYSENSE:1;
		uint8_t DECSCNM:1;
		uint8_t DECSCLM:1;
		uint8_t DECAWM:1;
		uint8_t SHIFTED:1;
		uint8_t POWER:1;
	}
	__attribute((packed)) bits;

	uint8_t brightness;
	uint8_t uart_rx;
	uint8_t uart_tx;
	
	uint8_t tabs[TABS_SIZE];

	uint8_t answerback[answerback_size];
}
__attribute((packed)) setting_t;

extern volatile setting_t setting;

#define __tab_array_indexval(arr, pos) (arr[pos >> 3])
#define __tab_array_bitmask(pos) __bitmask(pos & 0x07)
#define __tab_ishigh(var, pos)	__ishigh(__tab_array_indexval(var,pos),	__tab_array_bitmask(pos))
#define __tab_islow(var, pos) 	__islow(__tab_array_indexval(var,pos),	__tab_array_bitmask(pos))

#define setting_tab_high(pos) 	__high(__tab_array_indexval(setting.tabs, pos), __tab_array_bitmask(pos))
#define setting_tab_low(pos) 	__low(__tab_array_indexval(setting.tabs, pos), __tab_array_bitmask(pos))
#define setting_tab_flip(pos) 	__flip(__tab_array_indexval(setting.tabs, pos),__tab_array_bitmask(pos))
#define setting_tab_ishigh(pos) __tab_ishigh(setting.tabs, pos)
#define setting_tab_islow(pos) 	__tab_islow(setting.tabs, pos)

inline void setting_tabs_clear()
{
	uint8_t i = TABS_SIZE;

	while(i--)
	{
		setting.tabs[i] = 0;
	}
}

void setting_load(void);
void setting_store(void);

/* defined by hardware */
//setting_t parm_setting

#include <diy-vt100/port/setting.h>

#define parm_setting_tab_ishigh(pos) __tab_ishigh(parm_setting.tabs, pos)
#define parm_setting_tab_islow(pos) __tab_islow(parm_setting.tabs, pos)


#endif
