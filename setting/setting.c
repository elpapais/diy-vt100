#include <setting.h>

const struct __setting_nvr __setting_nvr;
uint8_t setting_brightness;
uint8_t setting_speed;
uint16_t setting_nvr_bits;
uint16_t setting_vr_bits;
uint16_t setting_tabs;

void setting_save()
{
	
}

void setting_load()
{
	setting_vr_bits = 0;
}


