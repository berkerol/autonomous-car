#include "PWM.h"

void PWM_Init() {
	//Change the function of the pin in here:
	IOCON_LEFT_MOTOR |= 3;
	IOCON_RIGHT_MOTOR |= 3;
	
	//Enable PCONP for PWM
	PCONP |= 1 << 5;
	
	//Enable PWM output for corresponding pin.
	PWM0->PCR |= (1 << 9) | (1 << 10);
	
	//Reset The PWM Timer Counter and The PWM Prescale Counter on the Next Positive Edge of PCLK
	PWM0->TCR |= (1 << 1);
	
	//Change MR0 Register value for giving pulse every 20 ms
	PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;
	
	//Reset TC, when MR0 matches TC.
	PWM0->MCR |= (1 << 1);
	
	//Enable PWM Match 0 Latch.
	PWM0->LER |= (1 << 0);	
	
	//Enable Counter and PWM and Clear Reset on the PWM
	uint32_t value = PWM0->TCR;
	value |= (1 << 0);
	value &= ~(1 << 1);
	PWM0->TCR = value;
	
	PWM_Left(0);
	PWM_Right(0);
}

void PWM_Left(uint32_t T_ON) {	
	if(T_ON > 100) {
		T_ON = 100;
	}
	
	T_ON = (uint32_t)(((PWM0->MR0) * T_ON) / 100);
	
	if (T_ON == PWM0->MR0) {
		T_ON++;
	}
	PWM0->MR1 = T_ON;
	
	//Enable PWM Match 1 Latch.
	PWM0->LER |= (1 << 1);
}

void PWM_Right(uint32_t T_ON) {	
	if(T_ON > 100) {
		T_ON = 100;
	}
	
	T_ON = (uint32_t)(((PWM0->MR0) * T_ON) / 100);
	
	if (T_ON == PWM0->MR0) {
		T_ON++;
	}
	PWM0->MR2 = T_ON;
	
	//Enable PWM Match 2 Latch.
	PWM0->LER |= (1 << 2);
}
