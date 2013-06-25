#ifndef VT100_ATTRIBUTE_H
#define VT100_ATTRIBUTE_H

#include <diy-vt100/common.h>

typedef struct
{
	uint8_t invert:1; 
	uint8_t underline:1; 
	uint8_t bold:1; 
	uint8_t blink:1;
}__attribute((packed)) dataprop_t;

#include <diy-vt100/screen.h>



typedef struct
{
	uint8_t double_width:1;
	
	uint8_t double_height:1;
	uint8_t double_height_pos:1; /* top:1 | bot:0 */
	
	/* lcd driver use (if mantaining buffer) */
	uint8_t touch:1;
}__attribute((packed)) rowprop_t;

extern rowprop_t vt100_rowprop[SCREEN_ROW];
extern dataprop_t vt100_dataprop;

void vt100_SGR(void);
void vt100_DECDWL(void);
void vt100_DECDHL_bottom(void);
void vt100_DECDHL_top(void);

#endif
