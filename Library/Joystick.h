#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"

#define JOYSTICK_PORT	PORT5
#define MOTOR_CONTROLLER_PORT PORT0
#define LED_PORT PORT0

#define JOYSTICK_LEFT_MASK		((uint32_t) 1 << 0)
#define JOYSTICK_DOWN_MASK		((uint32_t) 1 << 1)
#define JOYSTICK_UP_MASK			((uint32_t) 1 << 2)
#define JOYSTICK_CENTER_MASK	((uint32_t) 1 << 3)
#define JOYSTICK_RIGHT_MASK		((uint32_t) 1 << 4)

#define IN1 ((uint32_t) 1 << 0) //P9
#define IN2 ((uint32_t) 1 << 8) //P12
#define IN3 ((uint32_t) 1 << 7) //P13
#define IN4 ((uint32_t) 1 << 2) //P42

#define LED1 ((uint32_t) 1 << 21) //P8
#define LED2 ((uint32_t) 1 << 1) //P10
#define LED3 ((uint32_t) 1 << 4) //P34
#define LED4 ((uint32_t) 1 << 5) //P33

void Joystick_Init(void);
void Motor_Controller_Init(void);
void LED_Init(void);

uint8_t Joystick_Left_Pressed(void);
uint8_t Joystick_Down_Pressed(void);
uint8_t Joystick_Up_Pressed(void);
uint8_t Joystick_Center_Pressed(void);
uint8_t Joystick_Right_Pressed(void);
uint8_t Push_Button_Pressed(void);

extern uint8_t forwardFlag;

void turnOffLeds(void);
void frontLeds(void);
void backLeds(void);
void leftLeds(uint8_t value);
void rightLeds(uint8_t value);

void leftForward(void);
void leftBackward(void);
void leftStop(void);

void rightForward(void);
void rightBackward(void);
void rightStop(void);

void forward(void);
void backward(void);
void stop(void);

void IN1_Write(uint8_t value);
void IN2_Write(uint8_t value);
void IN3_Write(uint8_t value);
void IN4_Write(uint8_t value);

void LED1_Write(uint8_t value);
void LED2_Write(uint8_t value);
void LED3_Write(uint8_t value);
void LED4_Write(uint8_t value);

#endif
