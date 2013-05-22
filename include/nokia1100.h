
#ifndef _NOKIA1100_H_
#define _NOKIA1100_H_

#define NOKIA1100_WIDTH_PIXEL 96
#define NOKIA1100_HEIGHT_PIXEL 65

#define NOKIA1100_WIDTH_CHAR 6
#define NOKIA1100_HEIGHT_CHAR 8

#define NOKIA1100_COLOUMN 16
#define NOKIA1100_ROW 8

#define NOKIA1100_SCREEN_LOOP_SIZE 864

#include <common.h>

//yellow[10] gray blue green

/*
  PIN configuration:
  
  to know the pins, view the screen from front, pin 1 is on right side
  read : http://www.circuitvalley.com/2011/09/nokia-1100-lcd-interfacing-with.html
  example
    |-----------------|
    |  screen         |
    |    front        |
    |_________________|
     | | | | | | | | |
     1 2 3 4 5 6 7 8 9
     
     PIN 1: XRES AKA RESET
     PIN 2: XCS AKA SS
     PIN 3: GND
     PIN 4: SDA AKA MOSI
     PIN 5: SCLK AKA CLK
     PIN 6: VDDI
     PIN 7: VDD
     PIN 8: LED+
     PIN 9: Unused

	MSP_CONNECTION: 
	RESET 	= RESET
	SS 		= P1.0 
	MOSI 	= P1.1
	CLK 	= P1.2
*/

#define NOKIA1100_PDIR P2DIR
#define NOKIA1100_POUT P2OUT

#define NOKIA1100_SS 	BIT0
#define NOKIA1100_MOSI 	BIT1
#define NOKIA1100_CLK 	BIT2

/* settings */
#define NOKIA1100_INIT_CONTRAST 0x7F

void nokia1100_clear();
void nokia1100_init();
void nokia1100_send(uint16_t type);
void nokia1100_send_data_brustmode(const uint8_t send[], const uint16_t size);

#define nokia1100_gotoy(addr) \
			nokia1100_send_cmd(0xB0/* VERT ADDR */ | (addr & 0x0F))

#define nokia1100_gotox(addr) \
			nokia1100_send_cmd(0x00/* HORZ ADDR LSB */ | (addr & 0x0F)); \
			nokia1100_send_cmd(0x18/* HORZ ADDR MSB */ | ( (addr>>4)))

#define nokia1100_gotoyx(yaddr, xaddr) \
			nokia1100_gotoy(yaddr); \
			nokia1100_gotox(xaddr)
						
#define nokia1100_setinitrow_zero() \
			nokia1100_send_cmd(0x40  /* INITAL DISPLAY LINE */| 0x00)

#define nokia1100_send_data(data) \
			nokia1100_send(0x0100 | data)

#define nokia1100_send_cmd(data) \
			nokia1100_send(0x0000 | data)

#define nokia1100_showpixel_on() \
			nokia1100_send_cmd(0xAE /* DISPLAY POWER */ | 0x01)

#define nokia1100_showpixel_off() \
			nokia1100_send_cmd(0xAE/* DISPLAY POWER */ | 0x00); 

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

#define nokia1100_invertpixel_on() \
			nokia1100_send_cmd(0xA6/* PIXEL INVERT */ | 0x01)

#define nokia1100_invertpixel_off() \
			nokia1100_send_cmd(0xA6/* PIXEL INVERT */ | 0x00)

#define nokia1100_allpixel_on() \
			nokia1100_send_cmd(0xA4 /* PIXEL ALL */ | 0x01)

#define nokia1100_allpixel_off() 	\
			nokia1100_send_cmd(0xA4/* PIXEL ALL */ | 0x00)

#define nokia1100_contrast(value) \
			nokia1100_send_cmd(0x20 /* VOP-MSB */ | (value >> 5)); \
			nokia1100_send_cmd(0x80 /* VOP-LSB */ | (value & 0x1F)) 

#define nokia1100_chargepump_on() \
			nokia1100_send_cmd(0x2F/* CHARGE PUMP CONTROL */)

#define nokia1100_chargepump(value) \
			nokia1100_send_cmd(0x3D /* CHARGE PUMP */); \
			nokia1100_send_cmd(value & 0x03)

#define nokia1100_chargepump_off() \
			nokia1100_send_cmd(0x28 /* CHARGE PUMP CONTROL */ | 0x02)

#define nokia1100_addressingmode_vertical() \
			nokia1100_send_cmd(0xAA /* RAM ADDRESSING */ | 0x01)

#define nokia1100_addressingmode_horizontal() \
			nokia1100_send_cmd(0xAA /* RAM ADDRESSING */ | 0x00)

#endif /* _NOKIA1100_H_ */
