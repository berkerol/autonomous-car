#include "LPC407x_8x_177x_8x.h"
#include "Library/GPIO.h"
#include "Library/Joystick.h"
#include "Library/PWM.h"
#include "Library/Timer.h"
#include "Library/Ultrasonic.h"
#include "Library/External.h"
#include "Library/ADC.h"
#include "Parameters.h"

//Stores whether car is escaping from obstacle
uint8_t obstacleEscape = 0;
//Stores whether car is escaping from light source
uint8_t lightEscape = 0;
//Stores whether car is turning: negatives left, positives right
static int turning = 0;
 
void init() {
	Joystick_Init();
	Motor_Controller_Init();
	LED_Init();
	
	PWM_Init();
	
	Timer_Init();
	
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();
	Ultrasonic_Start_Trigger();
	
	//External_Init();
	currentMode = START_MODE;
	
	ADC_Init();
	
	stop();
	turnOffLeds();
	turning = 0;
}

void update() {
	//Read analog inputs
	trimpot = Trimpot_Read();
	ldrLeft = LDR_Left_Read();
	ldrRight = LDR_Right_Read();
	//Read push button
	if (Push_Button_Pressed()) {
		if (currentMode == 0) {
			currentMode = 1;
		} else {
			currentMode = 0;
		}
		stop();
		turnOffLeds();
		turning = 0;
		obstacleEscape = 0;
		lightEscape = 0;
		//Wait for button jump for half second
		for(int i = 0; i < 10000000; i++);
	}
	//Read ultrasonic interrupt
	if (ultrasonicSensorEdgeCount == 2) {
		int distance = (ultrasonicSensorFallingTime - ultrasonicSensorRisingTime) / 58;
		//Escape from obstacle
		if (obstacleEscape == 0 && forwardFlag == 1) {
			if (distance <= OBSTACLE_DISTANCE) {
				backward();
				backLeds();
				turning = 0;
				obstacleEscape = 1;
			}
		} else if (obstacleEscape == 1) {
			//Exit escaping from obstacle
			if (distance >= OBSTACLE_ESCAPE_DISTANCE) {
				forward();
				frontLeds();
				turning = 0;
				obstacleEscape = 0;
			}
		}
	}
	//Manual mode
	if (currentMode == 0 && obstacleEscape == 0) {
		//Escape from light source
		if (lightEscape == 0 && forwardFlag == 1) {
			if (ldrLeft < LIGHT_SOURCE) {
				forward();
				turning = 2;
				lightEscape = 1;
			} else if (ldrRight < LIGHT_SOURCE) {
				forward();
				turning = -2;
				lightEscape = 1;
			}
		} else if (lightEscape == 1) {
			//Exit escaping from light source
			if (ldrLeft > LIGHT_SOURCE && ldrRight > LIGHT_SOURCE) {
				forward();
				frontLeds();
				turning = 0;
				lightEscape = 0;
			}
		}
		//Move with Joystick
		if (Joystick_Up_Pressed() && lightEscape == 0) {
			forward();
			frontLeds();
			turning = 0;
		} else if (Joystick_Down_Pressed() && lightEscape == 0) {
			backward();
			backLeds();
			turning = 0;
		} else if (Joystick_Left_Pressed() && lightEscape == 0) {
			forward();
			turning = -2;
		} else if (Joystick_Right_Pressed() && lightEscape == 0) {
			forward();
			turning = 2;
		} else if (Joystick_Center_Pressed() && lightEscape == 0) {
			stop();
			turnOffLeds();
			turning = 0;
		}
	} else if (obstacleEscape == 0) { //Autonomous mode
		
		if (ldrLeft > ldrRight + LDR_DIFFERENCE_3) {
			forward();
			leftBackward();
			turning = -3;
		} else if (ldrRight > ldrLeft + LDR_DIFFERENCE_3) {
			forward();
			rightBackward();
			turning = 3;
		} else if (ldrLeft > ldrRight + LDR_DIFFERENCE_2) {
			forward();
			leftBackward();
			turning = -2;
		} else if (ldrRight > ldrLeft + LDR_DIFFERENCE_2) {
			forward();
			rightBackward();
			turning = 2;
		} else if (ldrLeft > ldrRight + LDR_DIFFERENCE_1) {
			forward();
			turning = -1;
		} else if (ldrRight > ldrLeft + LDR_DIFFERENCE_1) {
			forward();
			turning = 1;
		} else {
			forward();
			frontLeds();
			turning = 0;
		}
	}
	
	//Set motor speeds and LEDs
	if (turning == -3) {
		PWM_Left(trimpot);
		PWM_Right(trimpot);
		leftLeds(ledState);
	} else if (turning == -2) {		
		PWM_Left(trimpot * 4 / 5);
		PWM_Right(trimpot);
		leftLeds(ledState);
	} else if (turning == -1) {
		PWM_Left(trimpot * 4 / 5);
		PWM_Right(trimpot);
		leftLeds(ledState);
	} else if (turning == 1) {
		PWM_Left(trimpot);
		PWM_Right(trimpot * 4 / 5);
		rightLeds(ledState);
	} else if (turning == 2) {
		PWM_Left(trimpot);
		PWM_Right(trimpot * 4 / 5);
		rightLeds(ledState);
	} else if (turning == 3) {
		PWM_Left(trimpot);
		PWM_Right(trimpot);
		rightLeds(ledState);
	} else {
		PWM_Left(trimpot);
		PWM_Right(trimpot);
	}
}
 
int main() {
	init();
	
	while (1) {
		update();
	}
}
