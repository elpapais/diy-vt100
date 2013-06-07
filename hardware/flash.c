#include <hardware/flash.h>
#include <hardware/timer1_A3.h>
#include <setting.h>

const struct __setting flash_setting = 
{
	.brightness = TIMER1_A3_PWM_INIT,
	.speed = 0 /* 9600 */
};

void flash_setting_write()
{
	struct __setting *dest = (struct __setting *)(&flash_setting);
	
	__disable_interrupt();
	
	FCTL1 = FWKEY + ERASE;
	FCTL3 = FWKEY;

	dest->vr_bits = 0;
	
	FCTL1 = FWKEY + WRT;
	
	*dest = setting;
	
	FCTL1 = FWKEY;
	FCTL3 = FWKEY + LOCK;
	
	__enable_interrupt();
}

void flash_setting_read()
{
	setting = (struct __setting)flash_setting;
	setting.vr_bits = 0;

}
