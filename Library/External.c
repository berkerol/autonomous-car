#include "External.h"

uint8_t currentMode = 0;

void External_Init() {
  //Change the functionality of the push button as EINT0
  IOCON_PUSH_BUTTON |= 1;

  //Change the external interrupt mode as edge sensitive
  EXT->EXTMODE |= (1 << 0);

  //Enable interrupt for EINT0_IRQn
  NVIC_EnableIRQ(EINT0_IRQn);
}

void EINT0_IRQHandler() {
	if (currentMode == 0) {
		currentMode = 1;
	} else {
		currentMode = 0;
	}
  //Clear interrupt for EINT0
  EXT->EXTINT |= (1 << 0);
}
