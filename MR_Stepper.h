//
//  MR_Stepper.h
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#ifndef ____MR_Stepper__
#define ____MR_Stepper__

#include <Arduino.h>
#include "MR_IO.h"

#define MR_STEPPER_STEP_PIN 30
#define MR_STEPPER_DIR_PIN 31

void updateStepper(unsigned short int angle); // angle ragnes between 0 and 127

#endif /* defined(____MR_Stepper__) */
