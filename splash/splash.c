#include <splash.h>
#include <vt100/buffer.h>
#include <vt100/screen.h>
#include <vt100/cursor.h>

const struct __vt100_char splash_message[VT100_HEIGHT][VT100_WIDTH] = 
{
	{},
	{{' ', VT100_CHAR_PROP_DOUBLE_HEIGHT_TOP}, {' '}, {' '}, {'#'}, {'d'}, {'i'}, {'y'}, {'-'}, {'v'}, {'t'}, {'1'}, {'0'}, {'0'}, {' '}, {' '}, {' '}},
	{{' ', VT100_CHAR_PROP_DOUBLE_HEIGHT_BOTTOM}, {' '}, {' '}, {'#'}, {'d'}, {'i'}, {'y'}, {'-'}, {'v'}, {'t'}, {'1'}, {'0'}, {'0'}, {' '}, {' '}, {' '}}
};

//"   #diy-vt100   ",
//"   #diy-vt100   ",

void
splash()
{
	vt100_buffer_copy(splash_message);

	vt100_cursor.col = 0;
	vt100_cursor.row = 3;

	vt100_screen_refresh();
}
