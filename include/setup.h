#ifndef _SETUP_H_
#define _SETUP_H_

#include <common.h>
#include <state-machine.h>
#include <vt100/buffer.h>

/* note: (FALSE|TRUE) */

/* setup A options
 * SETUP_A_ONLINE: 	(online mode|offline mode)
 * SETUP_A_CPL : 	character per line(80|130)
 */

#define SETUP_A_ONLINE BIT0
#define SETUP_A_CPL BIT1
#define SETUP_A_TABS BIT2

/* 
 * setup B
 * SETUP_B_MODE: 	(vt52|ansi) 
 * SETUP_B_AUTO_X: 	auto XON & XOFF (OFF|ON)
 * SETUP_B_BPC: 		bits per character(7|8)
 * SETUP_B_CURSOR: 	cursor (block|underline)
 * SETUP_B_SHIFTED: 	#, EURO selection (#|EURO)
 * SEUTP_OPTB_POWER: 	(60Hz|50Hz)
 * SETUP_B_SCREEN:   (DARK|LIGHT)
 */
#define SETUP_B_CURSOR 		BIT0
#define SETUP_B_SCREEN 		BIT1 
#define SETUP_B_AUTOREPEAT 	BIT2
#define SETUP_B_SCROLL 		BIT3
#define SETUP_B_MARGINBELL 	BIT4
#define SETUP_B_KEYCLICK 	BIT5
#define SETUP_B_MODE 		BIT6
#define SETUP_B_AUTO_X 		BIT7
#define SETUP_B_SHIFTED 	BIT8
#define SETUP_B_WRAPAROUND 	BIT9
#define SETUP_B_NEWLINE 	BIT10
#define SETUP_B_INTERLACE 	BIT11
#define SETUP_B_PARITYSENSE BIT12
#define SETUP_B_PARITY 		BIT13
#define SETUP_B_BPC 		BIT14
#define SEUTP_B_POWER 		BIT15 /* ignore */

#define SETUP_ANSWERBACK_SIZE 20

struct __setup_setting
{
	uint8_t A;
	uint16_t B;
	uint8_t speed;
	uint8_t brightness;
	uint8_t answerback[SETUP_ANSWERBACK_SIZE];
};

extern bool_t setup_show;

#define SIZEOF_SETUP sizeof(struct __setup_setting)

const struct __vt100_char buffer_setupA[VT100_HEIGHT][VT100_WIDTH];
const struct __vt100_char buffer_setupB[VT100_HEIGHT][VT100_WIDTH];

extern struct __setup_setting setup_setting;

extern const struct __state setup_state_A[];
extern const struct __state setup_state_B[];
extern const struct __state setup_state_arrow[];
extern const struct __state setup_state_arrow_select[];

void setup();

void setup_state_worker();
void setup_switch_to_B();
void setup_switch_to_A();
void setup_B_flip();
void setup_A_flip();
void setup_arrow_right();
void setup_arrow_left();
void setup_arrow_down();
void setup_arrow_up();

#endif
