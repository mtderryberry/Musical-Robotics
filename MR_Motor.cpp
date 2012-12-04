//
//  MR_Motor.cpp
//
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_Motor.h"
bool DRIVE_MOTOR = false;

void MotorSetup() {
    pinMode(MR_MOTOR_PWM_PIN, OUTPUT);
    pinMode(MR_MOTOR_F_PIN, OUTPUT);
    pinMode(MR_MOTOR_R_PIN, OUTPUT);
	digitalWrite(MR_MOTOR_F_PIN, LOW);
	digitalWrite(MR_MOTOR_R_PIN, LOW);
	digitalWrite(MR_MOTOR_PWM_PIN, LOW);
}

void velocityControlMotor(int velocity, bool direction) {
	//direction assign
	if (direction) {
		digitalWrite(MR_MOTOR_F_PIN, HIGH);
		digitalWrite(MR_MOTOR_R_PIN, LOW);
	} else {
		digitalWrite(MR_MOTOR_F_PIN, LOW);
		digitalWrite(MR_MOTOR_R_PIN, HIGH);
	}

    //keep velocity within motor constraints
	velocity = constrain(velocity, 0, 127);
	velocity = map(velocity, 0, 127, 0, 255);

	//now assign speed control
    if (DRIVE_MOTOR) {
        analogWrite(MR_MOTOR_PWM_PIN, velocity);
    } else {
		analogWrite(MR_MOTOR_F_PIN, 0);
	}
}

//turn motor on
void EnableMotor() {
    DRIVE_MOTOR = true;
}

//turn motor off
void DisableMotor() {
    DRIVE_MOTOR = false;
}
