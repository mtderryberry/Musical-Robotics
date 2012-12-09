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

//timer to figure out when to turn off solenoid
unsigned int _SOLENOID_1_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_2_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_3_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_4_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_5_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_6_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_7_LAST_TRIGGER_TIME = 0;
unsigned int _SOLENOID_8_LAST_TRIGGER_TIME = 0;

//states used for diplaying status 
unsigned int _SOLENOID_1_STATE = 0;//assume 0 to be idle (returned and resting);
unsigned int _SOLENOID_2_STATE = 0;
unsigned int _SOLENOID_3_STATE = 0;
unsigned int _SOLENOID_4_STATE = 0;
unsigned int _SOLENOID_5_STATE = 0;
unsigned int _SOLENOID_6_STATE = 0;
unsigned int _SOLENOID_7_STATE = 0;
unsigned int _SOLENOID_8_STATE = 0;

//velocities used for controlling solenoids
unsigned int _SOLENOID_1_VEL = 0;//assume 0 to be idle (returned and resting);
unsigned int _SOLENOID_2_VEL = 0;
unsigned int _SOLENOID_3_VEL = 0;
unsigned int _SOLENOID_4_VEL = 0;
unsigned int _SOLENOID_5_VEL = 0;
unsigned int _SOLENOID_6_VEL = 0;
unsigned int _SOLENOID_7_VEL = 0;
unsigned int _SOLENOID_8_VEL = 0;

void SetupSolenoids() {
	pinMode(MR_SOLENOID_1_PIN, OUTPUT);
	pinMode(MR_SOLENOID_2_PIN, OUTPUT);
	pinMode(MR_SOLENOID_3_PIN, OUTPUT);
	pinMode(MR_SOLENOID_4_PIN, OUTPUT);
	pinMode(MR_SOLENOID_5_PIN, OUTPUT);
	pinMode(MR_SOLENOID_6_PIN, OUTPUT);
	pinMode(MR_SOLENOID_7_PIN, OUTPUT);
	pinMode(MR_SOLENOID_8_PIN, OUTPUT);
	digitalWrite(MR_SOLENOID_1_PIN, LOW);
	digitalWrite(MR_SOLENOID_2_PIN, LOW);
	digitalWrite(MR_SOLENOID_3_PIN, LOW);
	digitalWrite(MR_SOLENOID_4_PIN, LOW);
	digitalWrite(MR_SOLENOID_5_PIN, LOW);
	digitalWrite(MR_SOLENOID_6_PIN, LOW);
	digitalWrite(MR_SOLENOID_7_PIN, LOW);
	digitalWrite(MR_SOLENOID_8_PIN, LOW);
}

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

int convertVeltoTime(int vel) {
	if (vel==0) return 0;
	return MR_SOLENOID_MILLIS_PRESCALER * map(vel, 1, 127, _SOLENOID_MIN_ON_TIME, _SOLENOID_MAX_ON_TIME);
}

void handleSolenoids(){
	//group 1 and 2
	if (_SOLENOID_PAIR_1_MODE==0) {//normal mode
		if (millis() >= _SOLENOID_1_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_1_VEL)) {
			//kill solenoid one
			_SOLENOID_1_STATE = 0;
			_SOLENOID_1_VEL =0;
			digitalWrite(MR_SOLENOID_1_PIN, LOW);
		}
		if (millis() >= _SOLENOID_2_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_2_VEL)) {
			//kill solenoid two
			_SOLENOID_2_STATE = 0;
			_SOLENOID_2_VEL =0;
			digitalWrite(MR_SOLENOID_2_PIN, LOW);
		}
	} else if(_SOLENOID_PAIR_1_MODE==1){ //paired mode
		if (millis() >= _SOLENOID_1_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_1_VEL)){//we can release the attack
			_SOLENOID_1_STATE = 0;
			_SOLENOID_1_VEL =0;
			_SOLENOID_2_STATE = 0;
			_SOLENOID_2_VEL =0;
			digitalWrite(MR_SOLENOID_1_PIN, LOW);
			analogWrite(MR_SOLENOID_2_PIN, MR_SOLENOID_PAIRED_RETURN_DUTY_CYCLE);
		} else {//continue attacking
			digitalWrite(MR_SOLENOID_1_PIN, HIGH);
			digitalWrite(MR_SOLENOID_2_PIN, LOW);
		}
	}

	//group 3 and 4
	if (_SOLENOID_PAIR_2_MODE==0) {//normal mode
		if (millis() >= _SOLENOID_3_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_3_VEL)) {
			//kill solenoid one
			_SOLENOID_3_STATE = 0;
			_SOLENOID_3_VEL =0;
			digitalWrite(MR_SOLENOID_3_PIN, LOW);
		}
		if (millis() >= _SOLENOID_4_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_4_VEL)) {
			//kill solenoid two
			_SOLENOID_4_STATE = 0;
			_SOLENOID_4_VEL =0;
			digitalWrite(MR_SOLENOID_4_PIN, LOW);
		}
	} else if(_SOLENOID_PAIR_2_MODE==1){ //paired mode
		if (millis() >= _SOLENOID_3_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_3_VEL)){//we can release the attack
			_SOLENOID_3_STATE = 0;
			_SOLENOID_3_VEL =0;
			_SOLENOID_4_STATE = 0;
			_SOLENOID_4_VEL =0;
			digitalWrite(MR_SOLENOID_3_PIN, LOW);
			analogWrite(MR_SOLENOID_4_PIN, MR_SOLENOID_PAIRED_RETURN_DUTY_CYCLE);
		} else {//continue attacking
			digitalWrite(MR_SOLENOID_3_PIN, HIGH);
			digitalWrite(MR_SOLENOID_4_PIN, LOW);
		}
	}

	//group 5 and 6
	if (_SOLENOID_PAIR_3_MODE==0) {//normal mode
		if (millis() >= _SOLENOID_5_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_5_VEL)) {
			//kill solenoid one
			_SOLENOID_5_STATE = 0;
			_SOLENOID_5_VEL =0;
			digitalWrite(MR_SOLENOID_5_PIN, LOW);
		}
		if (millis() >= _SOLENOID_6_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_6_VEL)) {
			//kill solenoid two
			_SOLENOID_6_STATE = 0;
			_SOLENOID_6_VEL =0;
			digitalWrite(MR_SOLENOID_6_PIN, LOW);
		}
	} else if(_SOLENOID_PAIR_3_MODE==1){ //paired mode
		if (millis() >= _SOLENOID_5_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_5_VEL)){//we can release the attack
			_SOLENOID_5_STATE = 0;
			_SOLENOID_5_VEL =0;
			_SOLENOID_6_STATE = 0;
			_SOLENOID_6_VEL =0;
			digitalWrite(MR_SOLENOID_5_PIN, LOW);
			analogWrite(MR_SOLENOID_6_PIN, MR_SOLENOID_PAIRED_RETURN_DUTY_CYCLE);
		} else {//continue attacking
			digitalWrite(MR_SOLENOID_5_PIN, HIGH);
			digitalWrite(MR_SOLENOID_6_PIN, LOW);
		}
	}

	//group 7 and 8
	if (_SOLENOID_PAIR_4_MODE==0) {//normal mode
		if (millis() >= _SOLENOID_7_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_7_VEL)) {
			//kill solenoid one
			_SOLENOID_7_STATE = 0;
			_SOLENOID_7_VEL =0;
			digitalWrite(MR_SOLENOID_7_PIN, LOW);
		}
		if (millis() >= _SOLENOID_8_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_8_VEL)) {
			//kill solenoid two
			_SOLENOID_8_STATE = 0;
			_SOLENOID_8_VEL =0;
			digitalWrite(MR_SOLENOID_8_PIN, LOW);
		}
	} else if(_SOLENOID_PAIR_4_MODE==1){ //paired mode
		if (millis() >= _SOLENOID_7_LAST_TRIGGER_TIME + convertVeltoTime(_SOLENOID_7_VEL)){//we can release the attack
			_SOLENOID_7_STATE = 0;
			_SOLENOID_7_VEL =0;
			_SOLENOID_8_STATE = 0;
			_SOLENOID_8_VEL =0;
			digitalWrite(MR_SOLENOID_7_PIN, LOW);
			analogWrite(MR_SOLENOID_8_PIN, MR_SOLENOID_PAIRED_RETURN_DUTY_CYCLE);
		} else {//continue attacking
			digitalWrite(MR_SOLENOID_7_PIN, HIGH);
			digitalWrite(MR_SOLENOID_8_PIN, LOW);
		}
	}
}

void killSolenoid(unsigned short int solenoid) {
	switch (solenoid) {
		case 1:
			digitalWrite(MR_SOLENOID_1_PIN, LOW);
			_SOLENOID_1_STATE = 0;
			_SOLENOID_1_VEL = 0;
			break;
		case 2:
			digitalWrite(MR_SOLENOID_2_PIN, LOW);
			_SOLENOID_2_STATE = 0;
			_SOLENOID_2_VEL = 0;
			break;
		case 3:
			digitalWrite(MR_SOLENOID_3_PIN, LOW);
			_SOLENOID_3_STATE = 0;
			_SOLENOID_3_VEL = 0;
			break;
		case 4:
			digitalWrite(MR_SOLENOID_4_PIN, LOW);
			_SOLENOID_4_STATE = 0;
			_SOLENOID_4_VEL = 0;
			break;
		case 5:
			digitalWrite(MR_SOLENOID_5_PIN, LOW);
			_SOLENOID_5_STATE = 0;
			_SOLENOID_5_VEL = 0;
			break;
		case 6:
			digitalWrite(MR_SOLENOID_6_PIN, LOW);
			_SOLENOID_6_STATE = 0;
			_SOLENOID_6_VEL = 0;
			break;
		case 7:
			digitalWrite(MR_SOLENOID_7_PIN, LOW);
			_SOLENOID_7_STATE = 0;
			_SOLENOID_7_VEL = 0;
			break;
		case 8:
			digitalWrite(MR_SOLENOID_8_PIN, LOW);
			_SOLENOID_8_STATE = 0;
			_SOLENOID_8_VEL = 0;
			break;

		default:
			break;
	}
	
}

void triggerSolenoid(int number, int velocity) {
	if ((number == 1 || number == 2) && _SOLENOID_PAIR_1_MODE==1) {//paired mode
		_SOLENOID_1_LAST_TRIGGER_TIME = millis();
		_SOLENOID_2_LAST_TRIGGER_TIME = millis();
		_SOLENOID_1_STATE = 1;
		_SOLENOID_2_STATE = 1;
		_SOLENOID_1_VEL = velocity;
		_SOLENOID_2_VEL = 0;
		digitalWrite(MR_SOLENOID_1_PIN, HIGH);
		digitalWrite(MR_SOLENOID_2_PIN, LOW);
	}
	if ((number == 3 || number == 4) && _SOLENOID_PAIR_2_MODE==1) {//paired mode
		_SOLENOID_3_LAST_TRIGGER_TIME = millis();
		_SOLENOID_4_LAST_TRIGGER_TIME = millis();
		_SOLENOID_3_STATE = 1;
		_SOLENOID_4_STATE = 1;
		_SOLENOID_3_VEL = velocity;
		_SOLENOID_4_VEL = 0;
		digitalWrite(MR_SOLENOID_3_PIN, HIGH);
		digitalWrite(MR_SOLENOID_4_PIN, LOW);
	}
	if ((number == 5 || number == 6) && _SOLENOID_PAIR_3_MODE==1) {//paired mode
		_SOLENOID_5_LAST_TRIGGER_TIME = millis();
		_SOLENOID_6_LAST_TRIGGER_TIME = millis();
		_SOLENOID_5_STATE = 1;
		_SOLENOID_6_STATE = 1;
		_SOLENOID_5_VEL = velocity;
		_SOLENOID_6_VEL = 0;
		digitalWrite(MR_SOLENOID_5_PIN, HIGH);
		digitalWrite(MR_SOLENOID_6_PIN, LOW);
	}
	if ((number == 7 || number == 8) && _SOLENOID_PAIR_4_MODE==1) {//paired mode
		_SOLENOID_7_LAST_TRIGGER_TIME = millis();
		_SOLENOID_8_LAST_TRIGGER_TIME = millis();
		_SOLENOID_7_STATE = 1;
		_SOLENOID_8_STATE = 1;
		_SOLENOID_7_VEL = velocity;
		_SOLENOID_8_VEL = 0;
		digitalWrite(MR_SOLENOID_7_PIN, HIGH);
		digitalWrite(MR_SOLENOID_8_PIN, LOW);
	}
	//trigger standard solenoids
	if (number==1 && _SOLENOID_PAIR_1_MODE==0){
		_SOLENOID_1_LAST_TRIGGER_TIME = millis();
		_SOLENOID_1_STATE = 1;
		_SOLENOID_1_VEL = velocity;
		
		digitalWrite(MR_SOLENOID_1_PIN, HIGH);
	}
	if (number==2 && _SOLENOID_PAIR_1_MODE==0){
		_SOLENOID_2_LAST_TRIGGER_TIME = millis();
		_SOLENOID_2_STATE = 1;
		_SOLENOID_2_VEL = velocity;

		digitalWrite(MR_SOLENOID_2_PIN, HIGH);
	}

	if (number==3 && _SOLENOID_PAIR_2_MODE==0){
		_SOLENOID_3_LAST_TRIGGER_TIME = millis();
		_SOLENOID_3_STATE = 1;
		_SOLENOID_3_VEL = velocity;

		digitalWrite(MR_SOLENOID_3_PIN, HIGH);
	}
	if (number==4 && _SOLENOID_PAIR_2_MODE==0){
		_SOLENOID_4_LAST_TRIGGER_TIME = millis();
		_SOLENOID_4_STATE = 1;
		_SOLENOID_4_VEL = velocity;

		digitalWrite(MR_SOLENOID_4_PIN, HIGH);
	}

	if (number==5 && _SOLENOID_PAIR_3_MODE==0){
		_SOLENOID_5_LAST_TRIGGER_TIME = millis();
		_SOLENOID_5_STATE = 1;
		_SOLENOID_5_VEL = velocity;

		digitalWrite(MR_SOLENOID_5_PIN, HIGH);
	}
	if (number==6 && _SOLENOID_PAIR_3_MODE==0){
		_SOLENOID_6_LAST_TRIGGER_TIME = millis();
		_SOLENOID_6_STATE = 1;
		_SOLENOID_6_VEL = velocity;

		digitalWrite(MR_SOLENOID_6_PIN, HIGH);
	}

	if (number==7 && _SOLENOID_PAIR_4_MODE==0){
		_SOLENOID_7_LAST_TRIGGER_TIME = millis();
		_SOLENOID_7_STATE = 1;
		_SOLENOID_7_VEL = velocity;

		digitalWrite(MR_SOLENOID_7_PIN, HIGH);
	}
	if (number==8 && _SOLENOID_PAIR_4_MODE==0){
		_SOLENOID_8_LAST_TRIGGER_TIME = millis();
		_SOLENOID_8_STATE = 1;
		_SOLENOID_8_VEL = velocity;

		digitalWrite(MR_SOLENOID_8_PIN, HIGH);
	}
}

bool getSolenoidState(int number){
	int state = 0;
	switch (number) {
		case 1:
			state = _SOLENOID_1_STATE;
			break;
		case 2:
			state = _SOLENOID_2_STATE;
			break;
		case 3:
			state = _SOLENOID_3_STATE;
			break;
		case 4:
			state = _SOLENOID_4_STATE;
			break;
		case 5:
			state = _SOLENOID_5_STATE;
			break;
		case 6:
			state = _SOLENOID_6_STATE;
			break;
		case 7:
			state = _SOLENOID_7_STATE;
			break;
		case 8:
			state = _SOLENOID_8_STATE;
			break;
	}
	
	if (state==0) {
		return false;
	}
	return true;
}