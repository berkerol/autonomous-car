#include "Timer.h"

uint8_t ledState = 0;

void Timer_Init() {
	//Enable Timer0
	PCONP |= (1 << 1);

	//Change the mode of Timer0 to Timer Mode.
	TIMER0->CTCR &= ~(1 << 0) & ~(1 << 1);
	
	//Disable Timer Counter and Prescale Counter for Timer0.
	TIMER0->TCR &= ~(1 << 0);
	
	//Reset Timer Counter and Prescale Counter for Timer0.
	TIMER0->TCR |= (1 << 1);
	
	//Change PR Register value for 1 millisecond incrementing
	TIMER0->PR = PERIPHERAL_CLOCK_FREQUENCY / 1000 - 1;
	
	//Calculate the MR3 register value for giving 250 millisecond HIGH value
	TIMER0->MR3 = 250;

	//Interrupt, if MR3 register matches the TC.
	TIMER0->MCR |= (1 << 9);
	
	//Remove the reset on counters of Timer0.
	TIMER0->TCR &= ~(1 << 1);
	
	//Enable Timer0 Counter and Prescale Counter for counting.
	TIMER0->TCR |= (1 << 0);
	
	//Clear pendings for Timer0.
	NVIC_ClearPendingIRQ(TIMER0_IRQn);

	//Set Priority Timer0 IRQ as 5.
	NVIC_SetPriority(TIMER0_IRQn, 5);

	//Enable TIMER0_IRQn (Interrupt Request).
	NVIC_EnableIRQ(TIMER0_IRQn);
}

void TIMER0_IRQHandler() {
	if (ledState == 0) {
		ledState = 1;
	} else {
		ledState = 0;
	}
	TIMER0->IR |= (1 << 3);
	TIMER0->TC = 0;
}
