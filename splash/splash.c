#include <splash.h>

const char splash_message[5][16] = 
{
	{EXTASCII_BOX_TOPLEFT, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_TOPRIGHT},
	{EXTASCII_BOX_VERT, ' ', ' ', 'd', 'i', 'y', '-', 'v', 't', '1', '0', '0', ' ', ' ', ' ', EXTASCII_BOX_VERT},
	{EXTASCII_BOX_VERT, ' ', 'v', 't', '1', '0', '0', ' ', 'c', 'l', 'o', 'n', 'e', ' ', ' ', EXTASCII_BOX_VERT},
	{EXTASCII_BOX_VERT, '@', 'k', 'u', 'l', 'd', 'e', 'e', 'p', 'd', 'h', 'a', 'k', 'a', '9', EXTASCII_BOX_VERT},	
	{EXTASCII_BOX_BOTLEFT, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_HORZ, EXTASCII_BOX_BOTRIGHT}
};

//"┌──────────────┐",
//"│  diy-vt100   │",
//"│ vt100 clone  │",
//"│@kuldeepdhaka9│",
//"└──────────────┘"

void
splash()
{
	uint8_t i,j;
	for(i=0; i<5; i++)
	{
		/* NOTE: this can be moved with j loop buffer prop */
		vt100_buffer[i][0].prop |= VT100_BUFFER_PROP_TOUCH;
		
		for(j=0; j<16; j++)
		{
			vt100_buffer[i][j].data = splash_message[i][j];
			vt100_buffer[i][j].prop |= VT100_BUFFER_PROP_INVERSE;
		}
	}

	vt100_cursor.col = 0;
	vt100_cursor.row = 5;

	vt100_screen_refresh();
}
