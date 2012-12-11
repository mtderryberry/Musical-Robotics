//
//  MR_IO.cpp
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_IO.h"
#include "MR_MIDI.h"

//globals
bool DISPLAY_MENU = false;
unsigned long long int _debounce_lastpoll = 0;
unsigned short int _debounce_button = LOW;
MR_SETTING MR_SETTINGS_LIST[20];
unsigned short int _MR_SETTTINGS_LIST_INDEX = 0;
char* SCREEN_BUFFER = "Ready..."; //where to buffer the text that goes on the screen
char* MIDI_NOTE_STRING = "     ";
unsigned int MIDI_NOTE_VELOCITY_VAL = 0;
unsigned short int _LED_TIMER_1 = 0;
unsigned short int _LED_TIMER_2 = 0;
unsigned short int _LED_TIMER_3 = 0;
unsigned short int CURRENT_SETTING_NUMBER = 0;
unsigned short int CURRENT_SETTING_SELECTED_VALUE = 0;

int ENCODER_A_CURRENT_STATE = LOW;
int ENCODER_A_LAST_STATE = LOW;
int ENCODER_B_CURRENT_STATE = LOW;
int ENCODER_B_LAST_STATE = LOW;

extern short int _MIDI_channel;
extern short int _MIDI_velocity_min;
extern short int _MIDI_velocity_max;
extern short int _MIDI_velocity_curve;

void nextSetting() {
	if (DISPLAY_MENU) {
		CURRENT_SETTING_NUMBER = constrain(CURRENT_SETTING_NUMBER, 0, _MR_SETTTINGS_LIST_INDEX-2)+1;
		CURRENT_SETTING_SELECTED_VALUE = MR_SETTINGS_LIST[CURRENT_SETTING_NUMBER].value;
	}
}
void previousSetting() {
	if (DISPLAY_MENU) {
		CURRENT_SETTING_NUMBER = constrain(CURRENT_SETTING_NUMBER, 1, _MR_SETTTINGS_LIST_INDEX)-1;
		CURRENT_SETTING_SELECTED_VALUE = MR_SETTINGS_LIST[CURRENT_SETTING_NUMBER].value;
	}
}

void loadSetting(int index) {
	if (DISPLAY_MENU) {
		//MR_SETTINGS_LIST[index].value = EEPROM.read(index);
	}
}

void saveSetting(int index, int value) {
	if (DISPLAY_MENU) {
		//so the settings are changed
		value = constrain(value, 0, 255);
		//EEPROM.write(index, byte(value));

		//update based on case
		switch (index) {
			case 0:
				//don't update a variable yet
				break;
			case 1:
				MIDISetChannel(value);
				break;
			case 2:
				MIDIConfigureMinVel(value);
				break;
			case 3:
				MIDIConfigureMaxVel(value);
				break;
			case 4:
				MIDIConfigureCurVel(value);
				break;
			case 5:
				MIDISetTHRU(value);
				break;
			case 6:
				IODisplaySetBrightness(value);
				break;
			case 7:
				setSolenoidPairMode(1, value);
				break;
			case 8:
				setSolenoidPairMode(2, value);
				break;
			case 9:
				setSolenoidPairMode(3, value);
				break;
			case 10:
				setSolenoidPairMode(4, value);
				break;
			case 11:
				setSolenoidMinOnTime(value);
				break;
			case 12:
				setSolenoidMaxOnTime(value);
				break;
				
			default:
				//save nothing
				break;
		}
	}
}

void incrimentSetting() {
	if (DISPLAY_MENU) {
		int min = MR_SETTINGS_LIST[CURRENT_SETTING_NUMBER].min;
		int max = MR_SETTINGS_LIST[CURRENT_SETTING_NUMBER].max;
		CURRENT_SETTING_SELECTED_VALUE = constrain(CURRENT_SETTING_SELECTED_VALUE+1,min,max);
		//update setting
		MR_SETTINGS_LIST[CURRENT_SETTING_NUMBER].value = CURRENT_SETTING_SELECTED_VALUE;

		//based on setting number, update the setting
		saveSetting(CURRENT_SETTING_NUMBER, CURRENT_SETTING_SELECTED_VALUE);
	}
}

void decrimentSetting() {
	if (DISPLAY_MENU) {
		int min = MR_SETTINGS_LIST[CURRENT_SETTING_NUMBER].min;
		int max = MR_SETTINGS_LIST[CURRENT_SETTING_NUMBER].max;
		CURRENT_SETTING_SELECTED_VALUE = constrain(CURRENT_SETTING_SELECTED_VALUE,min+1,max)-1;
		//update setting
		MR_SETTINGS_LIST[CURRENT_SETTING_NUMBER].value = CURRENT_SETTING_SELECTED_VALUE;

		//based on setting number, update the setting
		saveSetting(CURRENT_SETTING_NUMBER, CURRENT_SETTING_SELECTED_VALUE);
	}
}

void parseEncoders() {
	if (DISPLAY_MENU){
		ENCODER_A_CURRENT_STATE = digitalRead(MR_ENCODER1_A_PIN);
		if ((ENCODER_A_LAST_STATE == LOW) && (ENCODER_A_CURRENT_STATE == HIGH)) {
			if (digitalRead(MR_ENCODER1_B_PIN) == HIGH) {
				//prev setting
				previousSetting();
			} else {
				//next setting
				nextSetting();
			}
		}
		ENCODER_A_LAST_STATE = ENCODER_A_CURRENT_STATE;

		ENCODER_B_CURRENT_STATE = digitalRead(MR_ENCODER2_A_PIN);
		if ((ENCODER_B_LAST_STATE == LOW) && (ENCODER_B_CURRENT_STATE == HIGH)) {
			if (digitalRead(MR_ENCODER2_B_PIN) == HIGH) {
				//dec setting
				decrimentSetting();
			} else {
				//inc setting
				incrimentSetting();
			}
		}
		ENCODER_B_LAST_STATE = ENCODER_B_CURRENT_STATE;
	}
}

MR_SETTING& _MR_AddGlobalSetting(char* n, int v, int m, int x) {
	MR_SETTING *temp = new MR_SETTING();
	temp->title = n;
	temp->value = v;
	temp->min = m;
	temp->max = x;
	
	return *temp;
}

void addSetting(char* n,int m, int x){
	MR_SETTINGS_LIST[_MR_SETTTINGS_LIST_INDEX++] = _MR_AddGlobalSetting(n, 1,m,x);//EEPROM.read(_MR_SETTTINGS_LIST_INDEX), m, x);
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
	brightness = brightness+127;
	MR_LCD_SERIAL_PORT.write(0x7C);
	MR_LCD_SERIAL_PORT.write( brightness );
	delay(200);
}

void IOPrintLCDChar(char toprint) {
	MR_LCD_SERIAL_PORT.write( byte(toprint) );
}

void IOPrintLCD( char *word ) {
	MR_LCD_SERIAL_PORT.print( word );
}

void DisplayMenu() {
	//poll encoders for values
	char tempbuffer[100];
	char* name = MR_SETTINGS_LIST[CURRENT_SETTING_NUMBER].title;
	strcpy(tempbuffer, name);

	//add enough whitespaces to jump to new line
	int i;
	for (i=0; i<16-strlen(name); i++) strcat(tempbuffer, " ");
	strcat(tempbuffer, "Value=");

	char vel[4];
	int tempvel = CURRENT_SETTING_SELECTED_VALUE;
	//itoa(tempvel, vel, 10);
	sprintf(vel, "%u", tempvel);
	strcat(tempbuffer, vel);

	//update the buffer
	SCREEN_BUFFER = tempbuffer;

	digitalWrite(MR_ENCODER1_LED_GREEN_PIN, LOW);
	digitalWrite(MR_ENCODER2_LED_GREEN_PIN, LOW);
	digitalWrite(MR_ENCODER1_LED_BLUE_PIN, HIGH);
	digitalWrite(MR_ENCODER2_LED_BLUE_PIN, HIGH);
}

void DisplayRealTimeStatus() {
	char tempbuffer[100];   // array to hold the result.

	strcpy(tempbuffer,"MIDI: "); // copy string one into the result.
	strcat(tempbuffer, MIDI_NOTE_STRING);
	strcat(tempbuffer, " @");
	
	char vel[4];
	int tempvel = MIDI_NOTE_VELOCITY_VAL;
	//itoa(tempvel, vel, 10);
	sprintf(vel, "%u", tempvel);
	strcat(tempbuffer, vel);

	int i;
	for (i=0; i<3-strlen(vel); i++) strcat(tempbuffer, " ");

	//add other screen buffer elements
	for (i=0; i<MR_NUM_SOLENOIDS; i++) {
		if (getSolenoidState(i+1)) {
			strcat(tempbuffer, "#");
		} else {
			strcat(tempbuffer, " ");
		}
	}
	strcat(tempbuffer, "  ");
	//update the buffer
	SCREEN_BUFFER = tempbuffer;

	digitalWrite(MR_ENCODER1_LED_GREEN_PIN, HIGH);
	digitalWrite(MR_ENCODER2_LED_GREEN_PIN, HIGH);
	digitalWrite(MR_ENCODER1_LED_BLUE_PIN, LOW);
	digitalWrite(MR_ENCODER2_LED_BLUE_PIN, LOW);
}

void ToggleMenu() {
	if (_debounce_lastpoll <= millis() + MR_ENC_DEBOUNCE_DELAY) {
		_debounce_lastpoll=millis();
		//read both pins
		unsigned short int val = digitalRead(MR_ENCODER1_BUTTON_PIN);
		if (val==LOW) val = digitalRead(MR_ENCODER2_BUTTON_PIN);

		//impliment only rising edge trigger
		if (val == HIGH && _debounce_button == LOW) {
			//toggle diplay menu
			blinkLED(1);
			blinkLED(2);
			blinkLED(3);
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

	pinMode(MR_ENCODER1_LED_BLUE_PIN, OUTPUT);
	pinMode(MR_ENCODER1_LED_GREEN_PIN, OUTPUT);
	pinMode(MR_ENCODER2_LED_BLUE_PIN, OUTPUT);
	pinMode(MR_ENCODER2_LED_GREEN_PIN, OUTPUT);

	pinMode(MR_ENCODER1_A_PIN, INPUT);
	pinMode(MR_ENCODER1_B_PIN, INPUT);
	pinMode(MR_ENCODER1_BUTTON_PIN, INPUT);
	pinMode(MR_ENCODER2_A_PIN, INPUT);
	pinMode(MR_ENCODER2_B_PIN, INPUT);
	pinMode(MR_ENCODER2_BUTTON_PIN, INPUT);

	digitalWrite(MR_ENCODER1_LED_GREEN_PIN, LOW);
	digitalWrite(MR_ENCODER2_LED_GREEN_PIN, LOW);
	digitalWrite(MR_ENCODER1_LED_BLUE_PIN, LOW);
	digitalWrite(MR_ENCODER2_LED_BLUE_PIN, LOW);
}
