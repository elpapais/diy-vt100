#include <diy-vt100/common.h>
#include <diy-vt100/hardware.h>

/*
 * usuage of setting bits 
 * setting.bits.HW_PRIV0 : cursor blink state
 * setting.bits.HW_PRIV1 : keyboard modifier
 * setting.bits.HW_PRIV2 : keyboard break
 * setting.bits.HW_PRIV3 : not used(maybe keybpard PARITY)
 * 
 * their maybe preprocessor directive to 
 * replace decscriptive names with their crossponding HW_PRIV#
 */

void hardware_reset(void)
{
	WDTCTL = 0;
}

bool_t hardware_malfunctioning(void)
{
	return FALSE;
}
