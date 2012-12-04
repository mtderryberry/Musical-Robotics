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
//extern SchedulerClass Scheduler;
extern char* SCREEN_BUFFER;
char* _OLD_SCREEN_BUFFER = "";
extern unsigned int MIDI_NOTE_VELOCITY_VAL;

void INIT() {
	//setup our I/O Pins
	IOInitializePins();

	//pretty script to give the lcd time to turn on
	int i;
	for (i=0; i < 5; i++){
		digitalWrite(MR_LED_1_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(20);               // wait for a second
		digitalWrite(MR_LED_1_PIN, LOW);    // turn the LED off by making the voltage LOW
		delay(20);               // wait for a second
		digitalWrite(MR_LED_2_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(20);               // wait for a second
		digitalWrite(MR_LED_2_PIN, LOW);    // turn the LED off by making the voltage LOW
		delay(20);
		digitalWrite(MR_LED_3_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(20);               // wait for a second
		digitalWrite(MR_LED_3_PIN, LOW);    // turn the LED off by making the voltage LOW
		delay(20);
	}

	//begin serial communication with LCD
	IOSetupLCD();

	//diaplay boot information
	IOClearLCD();
	IOPrintLCD("Booting.");
	delay(200);
	
	//begin MIDI on the default channel
	InitializeMIDI(MR_MIDI_DEFAULT_CHANNEL);

	IOClearLCD();
	IOPrintLCD("Booting..");
	delay(200);
	
	//initialize our thread functions as actual threads
	//Scheduler.startLoop(THREAD_MIDI_HANDLING);
	//Scheduler.startLoop(THREAD_GENERIC_IO);
	//Scheduler.startLoop(THREAD_UPDATE_GRAPHICS);
	//Scheduler.startLoop(THREAD_DISPLAY_DRIVER);
	//Scheduler.startLoop(THREAD_ROBOT_DRIVER);
	//Scheduler.startLoop(THREAD_NETWORK);
	
	IOClearLCD();
	IOPrintLCD("Booting...");
	delay(200);
	IODisplayON();

	//initialize global settings
	addSetting("Test", 5, 0, 100);
	
}

//setup our OS threads
//handles MIDI I/O
void THREAD_MIDI_HANDLING() {
	//parse the MIDI data
	MIDIBuffer();
	//yield();
}

//handles buttons and encoders
void THREAD_GENERIC_IO() {
	//impliment debouncing Finite State Machine for toggling menues

	handleLEDs();

	ToggleMenu();
	//delay(20);
	//yield();
}

//handles updating screen text
void THREAD_UPDATE_GRAPHICS() {
	//update screen buffer SCREEN_BUFFER
	if (DISPLAY_MENU) {
		DisplayMenu();
		//digitalWrite(MR_LED_3_PIN, HIGH);
	}
	else {
		DisplayRealTimeStatus();
		//digitalWrite(MR_LED_3_PIN, LOW);
	}

	//delay(200);
	//yield();
}

//actually drives serial display
void THREAD_DISPLAY_DRIVER() {
	//write serial data to the display every 200 uS
	//update display with SCREEN_BUFFER
	if (strcmp(_OLD_SCREEN_BUFFER, SCREEN_BUFFER) != 0) {
		//only update the screen if we have a different buffer
		IOClearLCD();
		char tmp[50];
		strcpy(tmp, SCREEN_BUFFER);
		IOPrintLCD(SCREEN_BUFFER);
		_OLD_SCREEN_BUFFER = tmp;
	}
	//wait for .2 s
	delay(2);
	//yield(); //this takes a while to do, and can be interrupted
}

//drives motors and other output
void THREAD_ROBOT_DRIVER() {
	//handle motors

	//handle solenoids

	//delay(20);
	//yield();
}

//inter-unit networking
void THREAD_NETWORK() {
	//leave this plank for now
}

void setup() {
	INIT();
}

void loop() {
	//yield();

	//temp mega code
	THREAD_MIDI_HANDLING();
	THREAD_GENERIC_IO();
	THREAD_UPDATE_GRAPHICS();
	THREAD_DISPLAY_DRIVER();
	THREAD_ROBOT_DRIVER();
	THREAD_NETWORK();
}