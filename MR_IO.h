//
//  MR_IO.h
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#ifndef ____MR_IO__
#define ____MR_IO__

#include "Arduino.h"
#include "MR_IO.h"

//define all basic IO pins
//ADC's
#define MR_POT_1_PIN 0
#define MR_POT_2_PIN 1
#define MR_POT_3_PIN 2

//GPIO's
#define MR_SWITCH_PIN 2
#define MR_LED_1_PIN 3
#define MR_LED_2_PIN 4
#define MR_LED_3_PIN 5
#define MR_LCD_PIN 10

#define MR_LCD_DEBUG_PIN 13

#define MR_LCD_SERIAL_PORT Serial
#define MR_LCD_SERIAL_BAUDRATE 9600

#define MR_IO_DEFAULT_LCD_BRIGHTNESS 30

#define MR_ENCODER_LED_RED_PIN 20
#define MR_ENCODER_LED_GREEN_PIN 45

extern bool DISPLAY_MENU;
extern unsigned short int _LCD_BRIGHTNESS;

void IOSetupLCD();
void IOClearLCD();
void IODIsplayON();
void IODisplayOFF();
void IODisplaySetBrightness(int brightness);
void IOPrintLCDChar(char toprint);
void IOPrintLCD( char word[] );
void DisplayMenu();
void DisplayRealTimeStatus();
void IOInitializePins();

#endif /* defined(____MR_IO__) */
