#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <diy-vt100/hardware/nokia1100.h>
#include <diy-vt100/hardware/timer1_A3.h>

#define SCREEN_WIDTH NOKIA1100_COLOUMN
#define SCREEN_HEIGHT NOKIA1100_ROW

#define SCREEN_BRIGHTNESS_MAX TIMER1_A3_PWM_MAX
#define SCREEN_BRIGHTNESS_MIN TIMER1_A3_PWM_MIN

#define screen_brightness(value) timer1_A3_pwm(value)
#define screen_send(data_arr, size) nokia1100_send_data(data_arr, size)

#endif
