#include <hardware/timer1_A3.h>

/* used for generating PWM for lcd */
void timer1_A3_init()
{
	/* P2.2/TA1.1 Output */
	P2DIR |= BIT2;
	
	/* TA1.1 Option select */
	P2SEL |= BIT2;
	
	/* Period Register */
	TIMER1_A3_TACCR0 = 256;

	/* TA1.1 25% dutycycle */
	TIMER1_A3_TACCR1 = TIMER1_A3_PWM_INIT;

	/* TA1CCR1, Reset/Set */
	TA1CCTL1 |= OUTMOD_7;

	/* timer1_A3 @ 512KHz */
	TIMER1_A3_TACTL = TASSEL_2 + ID_3  + MC_1 + TACLR;
}

void timer1_A3_pwm(uint8_t value)
{
	TIMER1_A3_TACCR1 = value;
	TIMER1_A3_TACTL = TASSEL_2 + ID_3  + MC_1 + TACLR;
}
