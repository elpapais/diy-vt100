#ifndef SETUP_H
#define SETUP_H

#include <diy-vt100/common.h>

extern uint8_t setup_number;

/* [LCD] */
void setupA_refresh(void);
void setupA_load(void);
void setupB_refresh(void);
void setupB_load(void);
void setup_show_wait(void);

void setup(void);
void setup_state_worker(void);
void setup_switch(void);
void setup_recall(void);
void setup_save(void);
void setup_reset(void);

void setup_value_flip(void);
void setup_next_setting(void);
void setup_previous_setting(void);

void setup_brightness_decrease(void);
void setup_brightness_increase(void);

void setup_uart_tx(void);
void setup_uart_rx(void);

void setup_TAB_flip(void);
void setup_TABS_clear(void);

void setup_LOCAL(void);
void setup_DECCOLM(void);

#endif
