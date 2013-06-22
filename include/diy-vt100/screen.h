#ifndef SCREEN_H
#define SCREEN_H

#define __NOKIA1100LCD__

#include <diy-vt100/common.h>

#ifdef __NOKIA1100LCD__
#include <diy-vt100/screen/nokia1100.h>
#else
#error "unkown LCD"
#endif

//typedef uint<size>_t row_t;
//typedef uint<size>_t col_t;

/* [LCD] */
//#define screen_row <CHAR>
//#define screen_col <CHAR>;
//#define screen_width <PIXEL>
//#define screen_height <PIXEL>
//#define screen_char_height <PIXEL>
//#define screen_char_width <PIXEL>

/* [LCD] */
void screen_invert(bool_t);

/* [LCD] */
void screen_gotorow(row_t);
void screen_gotocol(col_t);
void screen_shiftup();
void screen_row_clear(row_t);
void screen_full_clear();
void screen_segment_clear(row_t row, col_t start, col_t end);
void screen_putch();
void screen_splash();
void screen_init();

/* [hardware] */
//#define screen_brightness_max;
//#define screen_brightness_min;
void screen_brightness(uint8_t);

#endif
