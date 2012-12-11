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
extern unsigned short int CURRENT_SETTING_SELECTED_VALUE;
extern MR_SETTING* MR_SETTINGS_LIST;

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
	delay(200);
	IODisplaySetBrightness(2);
	delay(400);
	IODisplaySetBrightness(30);
	delay(400);
	//initialize global settings
	//don't change the order of these!
	addSetting("Awesomeness", 0, 100);//0
	addSetting("MIDI Channel", 1, 16);//1
	addSetting("Min Velocity", 0, 126);//2
	addSetting("Max Velocty", 1, 127);//3
	addSetting("Vel Curve", 1, 126);//4
	addSetting("Enable MIDI THRU", 0, 1);//5
	addSetting("Backlight", 1, 30);//6
	addSetting("Sol 1&2 Mode", 0, 1);//7
	addSetting("Sol 3&4 Mode", 0, 1);//8
	addSetting("Sol 5&6 Mode", 0, 1);//9
	addSetting("Sol 7&8 Mode", 0, 1);//10
	addSetting("S Min On Time", 1, 254);//11
	addSetting("S Max On Time", 2, 255);//12

	//initialize initial setting menu value
	CURRENT_SETTING_SELECTED_VALUE = 0;//EEPROM.read(0);

	//load the rest of the settings into our global variables
	for (i=0; i<_MR_SETTTINGS_LIST_INDEX; i++) {

		//looks pretty and gives time to handle lots of functionc alls
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

		saveSetting(i, MR_SETTINGS_LIST[i].value); //hacky way of reassigning to memory
	}
	delay(200);
	//bug fix to establish final brightness
	IODisplaySetBrightness(30);//EEPROM.read(6));
	delay(200);

	//directly read these to make absolutely sure we have the right values
	setSolenoidPairMode(1, 0);//EEPROM.read(7));
	setSolenoidPairMode(2, 0);//0);//EEPROM.read(8));
	setSolenoidPairMode(3, 0);//EEPROM.read(9));
	setSolenoidPairMode(4, 0);//EEPROM.read(10));

	//enable pins
	SetupSolenoids();

	//setup motor
	MotorSetup();
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
	//parse encoders
	parseEncoders();
	//impliment debouncing Finite State Machine for toggling menues
	ToggleMenu();
	//handle LED blinks
	handleLEDs();
	//delay(20);
	//yield();
}

//handles updating screen text
void THREAD_UPDATE_GRAPHICS() {
	//update screen buffer SCREEN_BUFFER based on current mode
	if (DISPLAY_MENU) DisplayMenu();
	else DisplayRealTimeStatus();

	delay(2);
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
	//handle motors <- maybe

	//handle solenoids
	handleSolenoids();
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