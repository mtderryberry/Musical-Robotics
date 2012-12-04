//
//  MRSolenoid.cpp
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_Solenoid.h"
unsigned short int _SOLENOID_PAIR_1_MODE = MR_SOLENOID_PAIR1_DEFAULT_MODE;
unsigned short int _SOLENOID_PAIR_2_MODE = MR_SOLENOID_PAIR2_DEFAULT_MODE;
unsigned short int _SOLENOID_PAIR_3_MODE = MR_SOLENOID_PAIR3_DEFAULT_MODE;
unsigned short int _SOLENOID_PAIR_4_MODE = MR_SOLENOID_PAIR4_DEFAULT_MODE;

unsigned short int _SOLENOID_MIN_ON_TIME =1;
unsigned short int _SOLENOID_MAX_ON_TIME = 255;

unsigned int _SOLENOID_1_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_2_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_3_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_4_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_5_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_6_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_7_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_8_LAST_TRIGGER_TIME = 0;

unsigned int _SOLENOID_1_STATE = 0;//assume 0 to be idle (returned and resting);
unsigned int _SOLENOID_2_STATE = 0;
unsigned int _SOLENOID_3_STATE = 0;
unsigned int _SOLENOID_4_STATE = 0;
unsigned int _SOLENOID_5_STATE = 0;
unsigned int _SOLENOID_6_STATE = 0;
unsigned int _SOLENOID_7_STATE = 0;
unsigned int _SOLENOID_8_STATE = 0;

void setSolenoidMinOnTime(int value){
	value = constrain(value, 1, 254);
	_SOLENOID_MIN_ON_TIME = value;
}

void setSolenoidMaxOnTime(int value){
	value = constrain(value, 2, 255);
	_SOLENOID_MAX_ON_TIME = value;
}

void setSolenoidPairMode(unsigned short int pair, unsigned short int mode){
	switch (pair) {
		case 1:
			_SOLENOID_PAIR_1_MODE = mode;
			break;
		case 2:
			_SOLENOID_PAIR_2_MODE = mode;
			break;
		case 3:
			_SOLENOID_PAIR_3_MODE = mode;
			break;
		case 4:
			_SOLENOID_PAIR_4_MODE = mode;
			break;
		default:
			break;
	}
}

void handleSolenoids(){
	
}

void triggerSolenoid(int number, int velocity) {
	
}