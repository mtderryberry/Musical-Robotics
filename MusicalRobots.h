//
//  MusicalRobots.h
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#ifndef ____MusicalRobots__
#define ____MusicalRobots__

#include "Arduino.h"
#include "MR_IO.h"
#include "MR_Solenoid.h"
#include "MR_Stepper.h"
#include "MR_Motor.h"

#include "MIDI.h"
#include "MR_MIDI.h"

extern bool DISPLAY_MENU;
extern MIDI_Class MIDI;

void INIT();

#endif /* defined(____MusicalRobots__) */
