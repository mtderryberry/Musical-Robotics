//
//  MR_MIDI.h
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#ifndef ____MR_MIDI__
#define ____MR_MIDI__

#include "arduino/Arduino.h"
#include "MR_IO.h"

//pins
#define MR_MIDI_IN_PIN 0
#define MR_MIDI_OUT_PIN 1
#define MR_MIDI_THRU_PIN 1

//config values
#define MR_MIDI_DEFAULT_CHANNEL 1 //default MIDI recieve and send channel
#define MR_MIDI_BAUDRATE 31250 //baudrate for MIDI communication
#define MR_MIDI_BUFFERSIZE 32 //size in bytes of the MIDI buffer queue
#define MR_MIDI_ENABLE_DEFAULT_THRU false //enable the default MIDI thru behavior

//define MIDI channels
#define MR_MIDI_CHANNEL_1 0x00
#define MR_MIDI_CHANNEL_2 0x01
#define MR_MIDI_CHANNEL_3 0x01
#define MR_MIDI_CHANNEL_4 0x03
#define MR_MIDI_CHANNEL_5 0x04
#define MR_MIDI_CHANNEL_6 0x05
#define MR_MIDI_CHANNEL_7 0x06
#define MR_MIDI_CHANNEL_8 0x07
#define MR_MIDI_CHANNEL_9 0x08
#define MR_MIDI_CHANNEL_10 0x09
#define MR_MIDI_CHANNEL_11 0x0A
#define MR_MIDI_CHANNEL_12 0x0B
#define MR_MIDI_CHANNEL_13 0x0C
#define MR_MIDI_CHANNEL_14 0x0D
#define MR_MIDI_CHANNEL_15 0x0E
#define MR_MIDI_CHANNEL_16 0x0F

void InitializeMIDI(int channel);
void _MIDIAddToBuffer(byte input);
int ReadMIDI();
#endif /* defined(____MR_MIDI__) */
