#ifndef SETUP_H
#define SETUP_H

#include <diy-vt100/common.h>
#include <diy-vt100/state-machine.h>
#include <diy-vt100/vt100/buffer.h>

extern uint8_t setup_number;

/* [LCD] */
void setupA_refresh();
void setupA_load();
void setupB_refresh();
void setupB_load();
void setup_save();

void setup();
void setup_state_worker();
void setup_switch();

void setup_value_flip();
void setup_next_setting();
void setup_previous_setting();

void setup_brightness_decrease();
void setup_brightness_increase();

void setup_uart_tx();
void setup_uart_rx();

void setup_TAB_flip();
void setup_TABS_clear();

void setup_LOCAL();
void setup_DECCOLM();

#endif
