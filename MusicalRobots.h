//
//  MusicalRobots.h
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#ifndef ____MusicalRobots__
#define ____MusicalRobots__

#include <Arduino.h>
//#include <EEPROM.h>
#include "MR_IO.h"
#include "MR_Solenoid.h"
#include "MR_Stepper.h"
#include "MR_Motor.h"

#include "MIDI.h"
#include "MR_MIDI.h"

#include <Scheduler.h>

extern bool DISPLAY_MENU;
extern MIDI_Class MIDI;
//extern SchedulerClass Scheduler;

void INIT();

void THREAD_MIDI_HANDLING();
void THREAD_GENERIC_IO();
void THREAD_UPDATE_GRAPHICS();
void THREAD_DISPLAY_DRIVER();
void THREAD_ROBOT_DRIVER();
void THREAD_NETWORK();

#endif /* defined(____MusicalRobots__) */
