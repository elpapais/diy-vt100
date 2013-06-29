#ifndef SCREEN_H
#define SCREEN_H

#include <diy-vt100/port/screen.h>
#include <diy-vt100/vt100/attribute.h>

typedef struct
{
	uint8_t data;
	dataprop_t prop;
} screench_t;

//typedef uint<size>_t row_t;
//typedef uint<size>_t col_t;

/* [LCD] */
//#define SCREEN_ROW <CHAR>
//#define SCREEN_COL <CHAR>;
//#define SCREEN_WIDTH <PIXEL>
//#define SCREEN_HEIGHT <PIXEL>
//#define SCREEN_CHAR_HEIGHT <PIXEL>
//#define SCREEN_CHAR_WIDTH <PIXEL>

/* [LCD] */
void screen_invert(bool_t);

/* [LCD] */
void screen_gotorow(row_t);
void screen_gotocol(col_t);

void screen_shiftup(void);
void screen_shiftdown(void);
void screen_putch(const uint8_t, const dataprop_t);

void screen_row_clear(const row_t i);
void screen_full_clear(void);
void screen_segment_clear(const row_t i, const col_t j_start, const col_t j_end);

void screen_row_copy(const row_t i, const screench_t buffer[SCREEN_COL]);
void screen_full_copy(const screench_t buffer[SCREEN_ROW][SCREEN_COL]);

/* fill screen with E's */
void screen_full_E(void);

/* [hardware] */
//#define SCREEN_BRIGHTNESS_MAX <interger>
//#define SCREEN_BRIGHTNESS_MIN <integer>
void screen_brightness(const uint8_t);

#endif
