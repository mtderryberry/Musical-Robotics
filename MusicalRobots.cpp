//
//  MusicalRobots.cpp
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//
#include "Scheduler.h"
#include "MusicalRobots.h"

//external variables
extern bool DISPLAY_MENU; //menu resource semaphore/mutex

void INIT() {
	//begin setting up timers

	//setup our I/O Pins
	IOInitializePins();

	//begin serial communication with LCD
	IOSetupLCD();

	//begin MIDI on the default channel
	InitializeMIDI(MR_MIDI_DEFAULT_CHANNEL);
}


//ARDUINO CODE
void setup() {
	//initialize our timers and other ISR's
	INIT();
}

void loop() {
	
}