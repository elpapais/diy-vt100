#include <splash.h>
#include <vt100/buffer.h>
#include <vt100/screen.h>
#include <vt100/cursor.h>

const struct __vt100_char splash_message[VT100_HEIGHT][VT100_WIDTH] = 
{
	{{' ', ROW_DOUBLE_HEIGHT_TOP | ROW_TOUCH}, {}, {}, {}, {'d'}, {'i'}, {'y'}, {'-'}, {'v'}, {'t'}, {'1'}, {'0'}, {'0'}, {' '}, {' '}, {' '}},
	{{' ', ROW_DOUBLE_HEIGHT_BOT | ROW_TOUCH}, {}, {}, {}, {'d'}, {'i'}, {'y'}, {'-'}, {'v'}, {'t'}, {'1'}, {'0'}, {'0'}, {' '}, {' '}, {' '}},
	{{0, ROW_TOUCH}, {'I'}, {'R'}, {'C'}, {' '}, {'#'}, {'d'}, {'i'}, {'y'}, {'-'}, {'v'}, {'t'}, {'1'}, {'0'}, {'0'}},
	{{0, ROW_TOUCH}},
	{{0, ROW_TOUCH}},
	{{0, ROW_TOUCH}},
	{{0, ROW_TOUCH}},
	{{0, ROW_TOUCH}},
};

//"   diy-vt100    ",
//"   diy-vt100    ",
//" IRC #diy-vt100 "

void
splash()
{
	vt100_buffer_copy(splash_message);

	vt100_cursor.col = 0;
	vt100_cursor.row = 3;

	vt100_screen_refresh();
}
