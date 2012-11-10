//
//  MR_IO.cpp
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_IO.h"

bool DISPLAY_MENU = true;
unsigned short int _LCD_BRIGHTNESS = MR_IO_DEFAULT_LCD_BRIGHTNESS;

char SCREEN_BUFFER[50] = "MUSICAL ROBOTS"; //where to buffer the text that goes on the screen

void IOSetupLCD() {
	MR_LCD_SERIAL_PORT.begin(MR_LCD_SERIAL_BAUDRATE);

	//set the initial brightness
	MR_LCD_SERIAL_PORT.write(0x7C);
	MR_LCD_SERIAL_PORT.write(byte(MR_IO_DEFAULT_LCD_BRIGHTNESS + 127));
}

void IOClearLCD() {
	MR_LCD_SERIAL_PORT.write(0x7C);
	MR_LCD_SERIAL_PORT.write(0x01);
}

void IODIsplayON() {
	MR_LCD_SERIAL_PORT.write(0x7C);
	MR_LCD_SERIAL_PORT.write(0x0C);
}

void IODisplayOFF() {
	MR_LCD_SERIAL_PORT.write(0x7C);
	MR_LCD_SERIAL_PORT.write(0x08);
}

void IODisplaySetBrightness(int brightness) {
	brightness = constrain(brightness, 1, 30);
	brightness = map(brightness, 1, 30, 128, 158);
	MR_LCD_SERIAL_PORT.write(0x7C);
	MR_LCD_SERIAL_PORT.write( byte(brightness) );
}

void IOPrintLCDChar(char toprint) {
	MR_LCD_SERIAL_PORT.write( byte(toprint) );
}

void IOPrintLCD( char *word ) {
	MR_LCD_SERIAL_PORT.write( word );
}

void DisplayMenu() {
	
}

void DisplayRealTimeStatus() {
	
}

void IOInitializePins() {
	
}
