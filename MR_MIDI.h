//
//  MR_MIDI.h
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#ifndef ____MR_MIDI__
#define ____MR_MIDI__

#include <Arduino.h>
#include "MR_IO.h"
#include "MR_Stepper.h"
#include "MR_Motor.h"
#include "MR_Solenoid.h"
#include "MIDI.h"

extern short int _MIDI_channel;
extern short int _MIDI_velocity_min;
extern short int _MIDI_velocity_max;
extern short int _MIDI_velocity_curve;
extern MIDI_Class MIDI;

//pins
#define MR_MIDI_IN_PIN 0 //default serial stuff
#define MR_MIDI_OUT_PIN 1 //default serial stuff
#define MR_MIDI_THRU_PIN 1 //default serial stuff

//config values
#define MR_MIDI_DEFAULT_CHANNEL 1 //default MIDI recieve and send channel
#define MR_MIDI_DEFAULT_THRU true

#define MR_MIDI_VELOCITY_DEFAUT_MIN 0
#define MR_MIDI_VELOCITY_DEFAUT_MAX 127
#define MR_MIDI_VELOCITY_DEFAUT_CURVE 64

void InitializeMIDI(int channel);
void MIDISetChannel(int channel);
int MIDIGetChannel();
int MIDIVelocityCurve(int rawVelocity);
void MIDIConfigureCurve(int min, int max, int curve);
void MIDIConfigureMinVel(int min);
void MIDIConfigureMaxVel(int max);
void MIDIConfigureCurVel(int curve);
void MIDISetTHRU(int value);
void MIDIBuffer();
void MIDIEnableThru();
void MIDIDisableThru();
void _handler_MIDI_Note_On(byte channel, byte note, byte velocity);
void _handler_MIDI_Note_Off(byte channel, byte note, byte velocity);
void _handler_MIDI_CC(byte channel, byte number, byte value);
void MIDIHandleNoteOn(int note, int rawVelocity);
void MIDIHandleNoteOff(int note, int scaledVelocity);
void MIDIHandleControlChange(int cc, int value);

#endif /* defined(____MR_MIDI__) */
