#include <vt100/vt100.h>

/* TODO's:
 * margin
 * tabulation
 * vt52 support
 * setup
 * led 
 * cursor save
 * cursor restore
 * support double width and double height in terminal (need support from device driver)
 */

struct __vt100
vt100;

void
vt100_keypad_appmode()
{
	vt100.mode.keypad = 1;
}

void
vt100_keypad_nummode()
{
	vt100.mode.keypad = 0;
}

void 
vt100_to_reset_state()
{
	/* TODO: set vt100 to reset state  */
}

void 
vt100_set_topbottom_margin()
{
	/* TODO: support margin */
}

void 
vt100_invoke_confidence_test()
{
	/* TODO: test the terminal */
}

