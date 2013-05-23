#include <vt100/control0.h>

void
vt100_bell()
{
	vt100_audio_bell();
}

void
vt100_backspace()
{
	vt100_param.count = 1;
	vt100_param.data[0] = 1;
	vt100_cursor_backward();
}
