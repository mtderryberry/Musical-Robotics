//
//  MR_Motor.cpp
//
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_Motor.h"

void setup() {
    pinMode(MR_MOTOR_PWM_PIN, INPUT);
    pinMode(MR_MOTOR_F_PIN, OUTPUT);
    pinMode(MR_MOTOR_R_PIN, OUTPUT);
}

void velocityControl(int velocity) {
    while(noteOn == true) {
        analogWrite(MR_MOTOR_F_PIN, velocity);
    }
    analogWrite(MR_MOTOR_F_PIN, 0);

}

void setNoteBooleanTrue() {
    noteOn = true;
}

void setNoteBooleanFalse() {
    noteOn = false;
}
