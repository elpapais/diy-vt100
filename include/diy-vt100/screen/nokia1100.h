#ifndef SCREEN_NOKIA1100_H
#define SCREEN_NOKIA1100_H

#include <diy-vt100/hardware/screen/nokia1100.h>
#include <diy-vt100/common.h>

/* VERT ADDR */
#define nokia1100_gotoy(addr) nokia1100_send_cmd(0xB0 | (addr & 0x0F))

#define nokia1100_gotox(addr) \
			/* HORZ ADDR LSB */ \
			nokia1100_send_cmd(0x00 | (addr & 0x0F)); \
			/* HORZ ADDR MSB */ \
			nokia1100_send_cmd(0x18 | ( (addr>>4)))

#define nokia1100_gotoyx(yaddr, xaddr) \
			nokia1100_gotoy(yaddr); \
			nokia1100_gotox(xaddr)

/* INITAL DISPLAY LINE */
#define nokia1100_setinitrow_zero()	nokia1100_send_cmd(0x40  | 0x00)

/* DISPLAY POWER */
#define nokia1100_showpixel_on() nokia1100_send_cmd(0xAE | 0x01)

/* DISPLAY POWER */
#define nokia1100_showpixel_off() nokia1100_send_cmd(0xAE | 0x00); 

#define nokia1100_power_on() \
			nokia1100_showpixel_on(); \
			nokia1100_allpixel_off(); \
			nokia1100_invertpixel_off()

#define nokia1100_power_off() \
			nokia1100_showpixel_off(); \
			nokia1100_allpixel_on()

#define nokia1100_power_partialoff() \
			nokia1100_showpixel_off(); \
			nokia1100_allpixel_off()

/* PIXEL INVERT */
#define nokia1100_invertpixel_on() 	nokia1100_send_cmd(0xA6 | 0x01)

/* PIXEL INVERT */
#define nokia1100_invertpixel_off() nokia1100_send_cmd(0xA6 | 0x00)

/* PIXEL ALL */
#define nokia1100_allpixel_on() nokia1100_send_cmd(0xA4 | 0x01)

/* PIXEL ALL */
#define nokia1100_allpixel_off() nokia1100_send_cmd(0xA4 | 0x00)

#define nokia1100_contrast(value) \
			/* VOP-MSB */ \
			nokia1100_send_cmd(0x20 | (value >> 5)); \
			/* VOP-LSB */ \
			nokia1100_send_cmd(0x80 | (value & 0x1F)) 

/* CHARGE PUMP CONTROL */
#define nokia1100_chargepump_on() nokia1100_send_cmd(0x2F)

/* CHARGE PUMP */
#define nokia1100_chargepump(value) \
			nokia1100_send_cmd(0x3D ); \
			nokia1100_send_cmd(value & 0x03)

/* CHARGE PUMP CONTROL */
#define nokia1100_chargepump_off() nokia1100_send_cmd(0x28 | 0x02)

/* RAM ADDRESSING */
#define nokia1100_addressingmode_vertical() nokia1100_send_cmd(0xAA  | 0x01)

/* RAM ADDRESSING */
#define nokia1100_addressingmode_horizontal() nokia1100_send_cmd(0xAA | 0x00)

void nokia1100_send_cmd (const uint8_t data);
void nokia1100_send_data(const uint8_t *data_array, const uint8_t size);
void nokia1100_full_clear();

typedef uint8_t row_t;
typedef uint8_t col_t;

#define SCREEN_ROW 8
#define SCREEN_COL 16
#define SCREEN_WIDTH 96
#define SCREEN_HEIGHT 65
#define SCREEN_CHAR_HEIGHT 8
#define SCREEN_CHAR_WIDTH 6

#endif
