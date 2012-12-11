//
//  MR_IO.h
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#ifndef ____MR_IO__
#define ____MR_IO__

#include <Arduino.h>
#include "MR_IO.h"

//define all basic IO pins

//GPIO's
#define MR_LED_1_PIN 48
#define MR_LED_2_PIN 46
#define MR_LED_3_PIN 47

#define MR_LCD_PIN 14
#define MR_LCD_DEBUG_PIN 14

#define MR_LCD_SERIAL_PORT Serial3
#define MR_LCD_SERIAL_BAUDRATE 9600

#define MR_IO_DEFAULT_LCD_BRIGHTNESS 30

#define MR_ENCODER1_LED_BLUE_PIN 8
#define MR_ENCODER1_LED_GREEN_PIN 7
#define MR_ENCODER2_LED_BLUE_PIN 3
#define MR_ENCODER2_LED_GREEN_PIN 2

#define MR_ENCODER1_A_PIN 10
#define MR_ENCODER1_B_PIN 11
#define MR_ENCODER1_BUTTON_PIN 9
#define MR_ENCODER2_A_PIN 6
#define MR_ENCODER2_B_PIN 5
#define MR_ENCODER2_BUTTON_PIN 4

#define MR_ENC_DEBOUNCE_DELAY 0
#define MR_LED_BLINK_DELAY_CYCLES 50

extern bool DISPLAY_MENU;

extern unsigned long long int _debounce_lastpoll;
extern unsigned short int _debounce_button;

struct MR_SETTING {
public:
	char* title;
	int value;
	int min;
	int max;
};

extern unsigned short int _MR_SETTTINGS_LIST_INDEX;

extern char* MIDI_NOTE_STRING;
extern unsigned int MIDI_NOTE_VELOCITY_VAL;

void IOSetupLCD();
void IOClearLCD();
void IODisplayON();
void IODisplayOFF();
void IODisplaySetBrightness(int brightness);
void IOPrintLCDChar(char toprint);
void IOPrintLCD( char word[] );
void DisplayMenu();
void DisplayRealTimeStatus();
void IOInitializePins();
void ToggleMenu();
void handleLEDs();
void blinkLED(unsigned short int led);
void parseEncoders();
void addSetting(char* n, int m, int x);
void nextSetting();
void previousSetting();
void loadSetting(int index);
void saveSetting(int index, int value);
void incrimentSetting();
void decrimentSetting();

#endif /* defined(____MR_IO__) */
