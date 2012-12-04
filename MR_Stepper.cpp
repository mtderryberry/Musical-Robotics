//
//  MR_Stepper.cpp
//
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_Stepper.h"
int currentDegrees = 0;

void stepperSetup() {
    pinMode(MR_STEPPER_STEP_PIN, OUTPUT);
    pinMode(MR_STEPPER_DIR_PIN, OUTPUT);
}

void stepMotor(int requestedDegrees) {
    int diff = requestedDegrees - currentDegrees;
    //FIX THIS. DOESN'T FIGURE OUT SHORTEST PATH. Will come back to tomorrow-ish.
    if(diff > 0) {
        digitalWrite(MR_STEPPER_DIR_PIN, HIGH);
        while(currentDegrees < requestedDegrees; currentDegrees++) {
            //for now, just a designated speed, can fix later
            analogWrite(MR_STEPPER_STEP_PIN, 120);
        }
    }
    else {
        digitalWrite(MR_STEPPER_DIR_PIN, LOW);
        while(currentDegrees > requestedDegrees; currentDegrees++) {
            //for now just a designated speed, can fix later
            analogWrite(MR_STEPPER_STEP_PIN, 60);
        }
    }
    digitalWrite(MR_STEPPER_STEP_PIN, LOW);

}

