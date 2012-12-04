//
//  MR_IO.cpp
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_IO.h"

//globals
bool DISPLAY_MENU = false;
unsigned long long int _debounce_lastpoll = 0;
unsigned short int _debounce_button = 0;
MR_SETTING MR_SETTINGS_LIST[20];
unsigned short int _MR_SETTTINGS_LIST_INDEX = 0;
char* SCREEN_BUFFER = "Ready..."; //where to buffer the text that goes on the screen
char* MIDI_NOTE_STRING = "     ";
unsigned int MIDI_NOTE_VELOCITY_VAL = 0;
unsigned short int _LED_TIMER_1 = 0;
unsigned short int _LED_TIMER_2 = 0;
unsigned short int _LED_TIMER_3 = 0;

MR_SETTING& _MR_AddGlobalSetting(char* n, int v, int m, int x) {
	MR_SETTING *temp = new MR_SETTING();
	temp->title = n;
	temp->value = v;
	temp->min = m;
	temp->max = x;
	
	return *temp;
}

void addSetting(char* n, int v, int m, int x){
	MR_SETTINGS_LIST[_MR_SETTTINGS_LIST_INDEX++] = _MR_AddGlobalSetting(n, v, m, x);
}

void IOSetupLCD() {
	MR_LCD_SERIAL_PORT.begin(MR_LCD_SERIAL_BAUDRATE);
}

void IOClearLCD() {
	MR_LCD_SERIAL_PORT.write(0xFE);
	MR_LCD_SERIAL_PORT.write(0x01);
}

void IODisplayON() {
	MR_LCD_SERIAL_PORT.write(0xFE);
	MR_LCD_SERIAL_PORT.write(0x0C);
}

void IODisplayOFF() {
	MR_LCD_SERIAL_PORT.write(0xFE);
	MR_LCD_SERIAL_PORT.write(0x08);
}

void IODisplaySetBrightness(int brightness) {
	brightness = constrain(brightness, 1, 30);
	brightness = map(brightness, 1, 30, 128, 158);
	MR_LCD_SERIAL_PORT.write(0xFE);
	MR_LCD_SERIAL_PORT.write( byte(brightness) );
}

void IOPrintLCDChar(char toprint) {
	MR_LCD_SERIAL_PORT.write( byte(toprint) );
}

void IOPrintLCD( char *word ) {
	MR_LCD_SERIAL_PORT.print( word );
}

void DisplayMenu() {
	//poll encoders for values
	SCREEN_BUFFER = "MAIN MENU";
}

void DisplayRealTimeStatus() {
	char tempbuffer[100];   // array to hold the result.

	strcpy(tempbuffer,"MIDI: "); // copy string one into the result.
	strcat(tempbuffer, MIDI_NOTE_STRING);
	strcat(tempbuffer, " @");
	
	char vel[4];
	int tempvel = MIDI_NOTE_VELOCITY_VAL;
	itoa(tempvel, vel, 10);
	strcat(tempbuffer, vel);

	//add other screen buffer elements
	

	//update the buffer
	SCREEN_BUFFER = tempbuffer;
}

void ToggleMenu() {
	if (_debounce_lastpoll > millis() + MR_ENC_DEBOUNCE_DELAY) {
		_debounce_lastpoll=millis();
		//read both pins
		unsigned short int val = digitalRead(MR_ENCODER1_BUTTON_PIN);
		if (val==0) val = digitalRead(MR_ENCODER2_BUTTON_PIN);

		//impliment only rising edge trigger
		if (val == 1 && _debounce_button == 0) {
			//toggle diplay menu
			DISPLAY_MENU = !DISPLAY_MENU;
		}

		//save our last recorded value regardless
		_debounce_button = val;
	}
}

void handleLEDs(){
	if (_LED_TIMER_1 == 0) digitalWrite(MR_LED_1_PIN, LOW);
	else _LED_TIMER_1--;

	if (_LED_TIMER_2== 0) digitalWrite(MR_LED_2_PIN, LOW);
	else _LED_TIMER_2--;

	if (_LED_TIMER_3 == 0) digitalWrite(MR_LED_3_PIN, LOW);
	else _LED_TIMER_3--;
}

void blinkLED(unsigned short int led){
	switch (led) {
		case 1:
			digitalWrite(MR_LED_1_PIN, HIGH);
			_LED_TIMER_1 = MR_LED_BLINK_DELAY_CYCLES;
			break;
		case 2:
			digitalWrite(MR_LED_2_PIN, HIGH);
			_LED_TIMER_2 = MR_LED_BLINK_DELAY_CYCLES;
			break;
		case 3:
			digitalWrite(MR_LED_3_PIN, HIGH);
			_LED_TIMER_3 = MR_LED_BLINK_DELAY_CYCLES;
			break;
		default:
			break;
	}
}

void IOInitializePins() {
	pinMode(MR_LED_1_PIN, OUTPUT);
	pinMode(MR_LED_2_PIN, OUTPUT);
	pinMode(MR_LED_3_PIN, OUTPUT);

	pinMode(MR_ENCODER1_LED_RED_PIN, OUTPUT);
	pinMode(MR_ENCODER1_LED_GREEN_PIN, OUTPUT);
	pinMode(MR_ENCODER2_LED_RED_PIN, OUTPUT);
	pinMode(MR_ENCODER2_LED_GREEN_PIN, OUTPUT);

	pinMode(MR_ENCODER1_A_PIN, INPUT);
	pinMode(MR_ENCODER1_B_PIN, INPUT);
	pinMode(MR_ENCODER1_BUTTON_PIN, INPUT);
	pinMode(MR_ENCODER2_A_PIN, INPUT);
	pinMode(MR_ENCODER2_B_PIN, INPUT);
	pinMode(MR_ENCODER2_BUTTON_PIN, INPUT);
}
