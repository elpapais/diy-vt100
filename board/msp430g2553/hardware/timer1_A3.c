#include <diy-vt100/common.h>
#include <diy-vt100/hardware/screen/nokia1100.h>

#define TIMER1_A3_TACTL TA1CTL
#define TIMER1_A3_TACCR0 TA1CCR0
#define TIMER1_A3_TACCR1 TA1CCR1

/* used for generating PWM for lcd */
void timer1_A3_init()
{
	/* P2.2/TA1.1 Output */
	P2DIR |= BIT2;
	
	/* TA1.1 Option select */
	P2SEL |= BIT2;
	
	/* Period Register */
	TIMER1_A3_TACCR0 = SCREEN_BRIGHTNESS_MAX + 1;

	/* TA1CCR1, Reset/Set */
	TA1CCTL1 |= OUTMOD_7;
}

void screen_brightness(const uint8_t value)
{
	/* TA1.1 dutycycle */
	TIMER1_A3_TACCR1 = value;
	
	/* timer1_A3 @ 512KHz */
	TIMER1_A3_TACTL = TASSEL_2 + ID_3  + MC_1 + TACLR;
}
