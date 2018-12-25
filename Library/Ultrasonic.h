#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "LPC407x_8x_177x_8x.h"

#include "GPIO.h"
#include "Timer.h"

#define IOCON_TRIGGER_ADDRESS 0x4002C024 //P11 P0_9
#define IOCON_TRIGGER	*((volatile uint32_t*)(IOCON_TRIGGER_ADDRESS))

#define IOCON_ECHO_ADDRESS 0x4002C060 //P16 P0_24
#define IOCON_ECHO	*((volatile uint32_t*)(IOCON_ECHO_ADDRESS))

void Ultrasonic_Trigger_Timer_Init(void);
void Ultrasonic_Capture_Timer_Init(void);
void Ultrasonic_Start_Trigger(void);

extern uint8_t ultrasonicSensorEdgeCount;
extern uint8_t isUltrasonicSensorTriggerEnded;

extern uint32_t ultrasonicSensorRisingTime;
extern uint32_t ultrasonicSensorFallingTime;
extern uint32_t ultrasonicSensorDuration;
extern uint32_t ultrasonicSensorDistance;

#endif
