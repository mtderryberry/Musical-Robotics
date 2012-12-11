//
//  MR_Stepper.cpp
//
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_Stepper.h"
int currentDegrees = 0;
unsigned short int steppermode = 0;
//0 for shortest path
//1 for always cw
//2 for always ccw

void stepperSetup() {
    pinMode(MR_STEPPER_STEP_PIN, OUTPUT);
    pinMode(MR_STEPPER_DIR_PIN, OUTPUT);
}



void updateStepper(unsigned short int angle) {
	
}
