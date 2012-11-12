//
//  MusicalRobots.cpp
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//
#include "MusicalRobots.h"

//external variables
extern bool DISPLAY_MENU; //menu resource semaphore/mutex
extern SchedulerClass Scheduler;
extern char* SCREEN_BUFFER;

void INIT() {
	//setup our I/O Pins
	IOInitializePins();

	//begin serial communication with LCD
	IOSetupLCD();

	//begin MIDI on the default channel
	InitializeMIDI(MR_MIDI_DEFAULT_CHANNEL);

	//initialize our thread functions as actual threads
	Scheduler.startLoop(THREAD_MIDI_HANDLING);
	Scheduler.startLoop(THREAD_GENERIC_IO);
	Scheduler.startLoop(THREAD_UPDATE_GRAPHICS);
	Scheduler.startLoop(THREAD_DISPLAY_DRIVER);
	Scheduler.startLoop(THREAD_ROBOT_DRIVER);
	Scheduler.startLoop(THREAD_NETWORK);
}

//setup our OS threads
//handles MIDI I/O
void THREAD_MIDI_HANDLING() {
	//parse the MIDI data
	MIDIBuffer();
	yield();
}

//handles buttons and encoders
void THREAD_GENERIC_IO() {
	//impliment debouncing Finite State Machine for toggling menues

	//parse quadrature encoders
	

	delay(20);
	yield();
}

//handles updating screen text
void THREAD_UPDATE_GRAPHICS() {
	//update screen buffer SCREEN_BUFFER
	if (DISPLAY_MENU) DisplayMenu();
	else DisplayRealTimeStatus();

	delay(200);
	yield();
}

//actually drives serial display
void THREAD_DISPLAY_DRIVER() {
	//write serial data to the display every 200 uS
	//update display with SCREEN_BUFFER
	IOClearLCD();
	IOPrintLCD(SCREEN_BUFFER);

	//wait for .2 s
	delay(400);
	yield(); //this takes a while to do, and can be interrupted
}

//drives motors and other output
void THREAD_ROBOT_DRIVER() {
	//handle motors

	//handle solenoids

	delay(20);
}

//inter-unit networking
void THREAD_NETWORK() {
	
}

//we'll update settings in the regular loop()
//save something for system idle process

void setup() {
	INIT();
}

void loop() {
	yield();
}