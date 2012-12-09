//
//  MRSolenoid.h
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#ifndef ____MRSolenoid__
#define ____MRSolenoid__

#include <Arduino.h>
#include "MR_IO.h"

#define MR_SOLENOID_1_PIN 27
#define MR_SOLENOID_2_PIN 25
#define MR_SOLENOID_3_PIN 28
#define MR_SOLENOID_4_PIN 29
#define MR_SOLENOID_5_PIN 26
#define MR_SOLENOID_6_PIN 24
#define MR_SOLENOID_7_PIN 52
#define MR_SOLENOID_8_PIN 53

#define MR_SOLENOID_PAIR1_DEFAULT_MODE 0
#define MR_SOLENOID_PAIR2_DEFAULT_MODE 0
#define MR_SOLENOID_PAIR3_DEFAULT_MODE 0
#define MR_SOLENOID_PAIR4_DEFAULT_MODE 0

#define MR_NUM_SOLENOIDS 8

#define MR_SOLENOID_PAIRED_RETURN_DUTY_CYCLE 64

#define MR_SOLENOID_MILLIS_PRESCALER 4

void SetupSolenoids();
void setSolenoidPairMode(unsigned short int pair, unsigned short int mode);
void setSolenoidMinOnTime(int value);
void setSolenoidMaxOnTime(int value);
void handleSolenoids();
void killSolenoid(unsigned short int solenoid);
void triggerSolenoid(int number, int velocity);
bool getSolenoidState(int number);
#endif /* defined(____MRSolenoid__) */
