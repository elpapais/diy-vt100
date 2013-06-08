#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <hardware/ic_74xx595.h>

#define BUZZER 	IC_74xx595_PIN0

#define buzzer_on() ic_74xx595_high(BUZZER)
#define buzzer_off() ic_74xx595_low(BUZZER)

#endif
