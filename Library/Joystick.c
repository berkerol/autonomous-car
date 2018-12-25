#include "Joystick.h"

void Joystick_Init() {
	GPIO_DIR_Write(JOYSTICK_PORT, JOYSTICK_LEFT_MASK, INPUT);
	GPIO_DIR_Write(JOYSTICK_PORT, JOYSTICK_DOWN_MASK, INPUT);
	GPIO_DIR_Write(JOYSTICK_PORT, JOYSTICK_UP_MASK, INPUT);
	GPIO_DIR_Write(JOYSTICK_PORT, JOYSTICK_CENTER_MASK, INPUT);
	GPIO_DIR_Write(JOYSTICK_PORT, JOYSTICK_RIGHT_MASK, INPUT);
}

void Motor_Controller_Init() {
	GPIO_DIR_Write(MOTOR_CONTROLLER_PORT, IN1, OUTPUT);
	GPIO_DIR_Write(MOTOR_CONTROLLER_PORT, IN2, OUTPUT);
	GPIO_DIR_Write(MOTOR_CONTROLLER_PORT, IN3, OUTPUT);
	GPIO_DIR_Write(MOTOR_CONTROLLER_PORT, IN4, OUTPUT);
}

void LED_Init() {
	GPIO_DIR_Write(LED_PORT, LED1, OUTPUT);
	GPIO_DIR_Write(LED_PORT, LED2, OUTPUT);
	GPIO_DIR_Write(LED_PORT, LED3, OUTPUT);
	GPIO_DIR_Write(LED_PORT, LED4, OUTPUT);
}

uint8_t Joystick_Left_Pressed(void) {
	if (GPIO_PIN_Read(JOYSTICK_PORT, JOYSTICK_LEFT_MASK) == 0) {
		return 1;
	}
	return 0;
}

uint8_t Joystick_Down_Pressed(void) {
	if (GPIO_PIN_Read(JOYSTICK_PORT, JOYSTICK_DOWN_MASK) == 0) {
		return 1;
	}
	return 0;
}

uint8_t Joystick_Up_Pressed(void) {
	if (GPIO_PIN_Read(JOYSTICK_PORT, JOYSTICK_UP_MASK) == 0) {
		return 1;
	}
	return 0;
}

uint8_t Joystick_Center_Pressed(void) {
	if (GPIO_PIN_Read(JOYSTICK_PORT, JOYSTICK_CENTER_MASK) == 0) {
		return 1;
	}
	return 0;
}

uint8_t Joystick_Right_Pressed(void) {
	if (GPIO_PIN_Read(JOYSTICK_PORT, JOYSTICK_RIGHT_MASK) == 0) {
		return 1;
	}
	return 0;
}

uint8_t Push_Button_Pressed(void) {
	if (GPIO_PIN_Read(PORT2, (1 << 10)) == 0) {
		return 1;
	}
	return 0;
}

uint8_t forwardFlag = 0;

void turnOffLeds() {
	LED1_Write(LOW);
	LED2_Write(LOW);
	LED3_Write(LOW);
	LED4_Write(LOW);
	forwardFlag = 0;
}

void frontLeds() {
	LED1_Write(HIGH);
	LED2_Write(LOW);
	LED3_Write(HIGH);
	LED4_Write(LOW);
	forwardFlag = 1;
}

void backLeds() {
	LED1_Write(LOW);
	LED2_Write(HIGH);
	LED3_Write(LOW);
	LED4_Write(HIGH);
	forwardFlag = 0;
}

void leftLeds(uint8_t value) {
	LED1_Write(value);
	LED2_Write(value);
	LED3_Write(LOW);
	LED4_Write(LOW);
	forwardFlag = 0;
}

void rightLeds(uint8_t value) {
	LED1_Write(LOW);
	LED2_Write(LOW);
	LED3_Write(value);
	LED4_Write(value);
	forwardFlag = 0;
}

void leftForward() {
	IN1_Write(HIGH);
	IN2_Write(LOW);
}

void leftBackward() {
	IN1_Write(LOW);
	IN2_Write(HIGH);
}

void leftStop() {
	IN1_Write(LOW);
	IN2_Write(LOW);
}

void rightForward() {
	IN3_Write(HIGH);
	IN4_Write(LOW);
}

void rightBackward() {
	IN3_Write(LOW);
	IN4_Write(HIGH);
}

void rightStop() {
	IN3_Write(LOW);
	IN4_Write(LOW);
}

void forward() {
	leftForward();
	rightForward();
}

void backward() {
	leftBackward();
	rightBackward();
}

void stop() {
	leftStop();
	rightStop();
}

void IN1_Write(uint8_t value) {
	GPIO_PIN_Write(MOTOR_CONTROLLER_PORT, IN1, value);
}

void IN2_Write(uint8_t value) {
	GPIO_PIN_Write(MOTOR_CONTROLLER_PORT, IN2, value);
}

void IN3_Write(uint8_t value) {
	GPIO_PIN_Write(MOTOR_CONTROLLER_PORT, IN3, value);
}

void IN4_Write(uint8_t value) {
	GPIO_PIN_Write(MOTOR_CONTROLLER_PORT, IN4, value);
}

void LED1_Write(uint8_t value) {
	GPIO_PIN_Write(LED_PORT, LED1, value);
}

void LED2_Write(uint8_t value) {
	GPIO_PIN_Write(LED_PORT, LED2, value);
}

void LED3_Write(uint8_t value) {
	GPIO_PIN_Write(LED_PORT, LED3, value);
}

void LED4_Write(uint8_t value) {
	GPIO_PIN_Write(LED_PORT, LED4, value);
}
