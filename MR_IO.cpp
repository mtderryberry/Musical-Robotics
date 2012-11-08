//
//  MR_IO.cpp
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_IO.h"
void IOSetupLCD() {
	Serial1.begin();
}

void IOClearLCD() {

}

void IODIsplayON() {

}

void IODisplayOFF() {
	
}

void IOPrintLCDChar(char toprint) {
	Serial1.write( byte(toprint) );
}

void IOPrintLCD( char word[] ) {
	Serial1.write( word );
}
