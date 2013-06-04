#ifndef _SETUP_H_
#define _SETUP_H_

#include <common.h>
#include <state-machine.h>
#include <vt100/buffer.h>
#include <msp430.h>

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
#define SETUP_B_NEWLINE 	BITA
#define SETUP_B_INTERLACE 	BITB
#define SETUP_B_PARITYSENSE BITC
#define SETUP_B_PARITY 		BITD
#define SETUP_B_BPC 		BITE
#define SETUP_B_POWER 		BITF /* ignore */

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
extern uint8_t setup_type_current;
extern uint8_t setup_setting_number;

extern const struct __state setup_state_type[];
extern const struct __state setup_state_arrow[];
extern const struct __state setup_state_arrow_select[];

void setup();

void setup_new_value(row_t row, col_t col, bool_t val, uint8_t value_no);
void setup_A_refresh();
void setup_B_refresh();
void setup_switch();
void setup_value_flip();
void setup_arrow_right();
void setup_arrow_left();
void setup_arrow_down();
void setup_arrow_up();
void setup_state_worker();

#endif
