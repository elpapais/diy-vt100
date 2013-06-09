#ifndef _SETUP_H_
#define _SETUP_H_

#include <common.h>
#include <state-machine.h>
#include <vt100/buffer.h>
#include <msp430.h>

extern bool_t setup_show;

extern const struct __vt100_char setup_buffer_A[VT100_HEIGHT][VT100_WIDTH];
extern const struct __vt100_char setup_buffer_B[VT100_HEIGHT][VT100_WIDTH];

extern uint8_t setup_type_current;
extern uint8_t setup_setting_number;

extern const struct __state setup_state_type[];
extern const struct __state setup_state_arrow[];
extern const struct __state setup_state_arrow_select[];

void setup();

void setup_A_refresh();
void setup_B_refresh();
void setup_switch();

void setup_state_worker();

void setup_save();
void setup_reset();
void setup_reload();

void setup_value_flip();
void setup_next_setting();
void setup_previous_setting();
void setup_brightness_decrease();
void setup_brightness_increase();
void setup_speed();
void setup_TAB_flip();
void setup_TABS_clear();
void setup_LOCAL();
void setup_DECCOLM();

#endif
