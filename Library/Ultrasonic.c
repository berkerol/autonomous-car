#include "Ultrasonic.h"

void Ultrasonic_Trigger_Timer_Init() {
  IOCON_TRIGGER |= 0x03;

  PCONP |= 1 << 22;

  TIMER2->CTCR = 0x00;

  TIMER2->TCR &= ~(1 << 0);

  TIMER2->TCR |= (1 << 1);

  TIMER2->PR = PERIPHERAL_CLOCK_FREQUENCY / 1000000 - 1;

  //Write the correct configuration for EMR (Toggle output value and initial value is HIGH)
  TIMER2->EMR |= (1 << 3) | (1 << 10) | (1 << 11);

  //Enable TIMER2_IRQn (Interrupt request)
  NVIC_EnableIRQ(TIMER2_IRQn);

  //Set priority TIMER2_IRQn as 5
  NVIC_SetPriority(TIMER2_IRQn, 5);

  //Clear pendings for Timer2
  NVIC_ClearPendingIRQ(TIMER2_IRQn);
}

void Ultrasonic_Capture_Timer_Init() {
  IOCON_ECHO |= 0x03;

  PCONP |= 1 << 23;

  TIMER3->CTCR = 0x00;

  TIMER3->TCR &= ~(1 << 0);

  TIMER3->TCR |= (1 << 1);

  TIMER3->PR = PERIPHERAL_CLOCK_FREQUENCY / 1000000 - 1;

  TIMER3->CCR = (1 << 3) | (1 << 4) | (1 << 5);

  TIMER3->TCR &= ~(1 << 1);

  TIMER3->TCR |= (1 << 0);
}

void Ultrasonic_Start_Trigger() {
  //Give correct value to MR3 register for 10 microsecond
  TIMER2->MR3 = 10;

  //Enable interrupt for MR3 register, if MR3 register matches the TC
  TIMER2->MCR |= (1 << 9);

  //Remove the reset on counters of Timer2
  TIMER2->TCR &= ~(1 << 1);

  //Enable Timer2 counter and prescale counter for counting
  TIMER2->TCR |= 1 << 0;
}

uint8_t isUltrasonicSensorTriggerEnded = 0;
uint8_t ultrasonicSensorEdgeCount = 0;

void TIMER2_IRQHandler() {
  if (isUltrasonicSensorTriggerEnded == 0) {
    //Change MR3 register value for suggested waiting
    TIMER2->MR3 = 60000;

    isUltrasonicSensorTriggerEnded = 1;

    ultrasonicSensorEdgeCount = 0;

    //Clear pendings for Timer3
    NVIC_ClearPendingIRQ(TIMER3_IRQn);

    //Enable TIMER3_IRQn (Interrupt request)
    NVIC_EnableIRQ(TIMER3_IRQn);
  }
  else {
    TIMER2->MR3 = 10;
    isUltrasonicSensorTriggerEnded = 0;
  }

  //Clear IR register flag for corresponding interrupt
  TIMER2->IR |= (1 << 3);

  TIMER2->TC = 0;
}

uint32_t ultrasonicSensorRisingTime = 0;
uint32_t ultrasonicSensorFallingTime = 0;
uint32_t ultrasonicSensorDuration = 0;
uint32_t ultrasonicSensorDistance = 0;

void TIMER3_IRQHandler() {
  if (ultrasonicSensorEdgeCount == 0) {
    ultrasonicSensorRisingTime = TIMER3->CR1;

    ultrasonicSensorEdgeCount = 1;

    NVIC_ClearPendingIRQ(TIMER3_IRQn);
  }
  else if (ultrasonicSensorEdgeCount == 1) {
    ultrasonicSensorFallingTime = TIMER3->CR1;

    ultrasonicSensorEdgeCount = 2;

    //Clear pendings for Timer3
    NVIC_ClearPendingIRQ(TIMER3_IRQn);

    //Disable TIMER3_IRQn (Interrupt request)
    NVIC_DisableIRQ(TIMER3_IRQn);
  }

  TIMER3->IR = 1 << 5;
}
