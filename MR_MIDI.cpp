//
//  MR_MIDI.cpp
//  
//
//  Created by Rayce Stipanovich on 11/1/12.
//
//

#include "MR_MIDI.h"
//initialize our channel to our default channel
static short int _MIDI_channel = MR_MIDI_DEFAULT_CHANNEL;
static byte _MIDI_buffer[MR_MIDI_BUFFERSIZE];
static int _MIDI_buffer_queue_size -1;

/*========================================
 FUNCTION:	InitializeMIDI
 USAGE:		Called to initialize the MIDI communications
			protocol at the standard MIDI baudrate.
========================================*/
void InitializeMIDI(int channel = MR_MIDI_DEFAULT_CHANNEL) {
	//establish serial communications over default serial ports
	Serial.begin(MR_MIDI_BAUDRATE);

	//update our MIDI channel if need be
	_MIDI_channel = constrain(channel, 1 ,16);
}

/*========================================
 FUNCTION:	_MIDIAddToBuffer
 USAGE:		Called to initialize the MIDI communications
 protocol at the standard MIDI baudrate.
 ========================================*/
void _MIDIAddToBuffer(byte input) {
	//prevent segfults
	if (_MIDI_buffer_queue_size - 1 < MR_MIDI_BUFFERSIZE) {
		//we have room in our buffer
		_MIDI_buffer[++_MIDI_buffer_queue_size] = input;
	}
}

/*========================================
 FUNCTION:	ReadMIDI
 USAGE:		Reads MIDI into the _MIDI_buffer array
			in case code executes too slowly.
 RETURNS:	INT bytes successfully read.
 ========================================*/
int ReadMIDI(){
	int bytesread = 0;
	
	//see if there is serial data
	if (Serial.available() > 0){
		byte _MIDIByte = byte(Serial.read());
		
		//so we have MIDI data!  Let's see if it's for us
		//are we on the right channel?
		//extract the MIDI channel low nibble (4 LSB's)
		byte _MIDIByteChannel = 0x0F & _MIDIByte;
		if (_MIDIByteChannel == _MIDI_channel) {
			//this matches our channel -> add it to the buffer
			_MIDIAddToBuffer(_MIDIByte);
			bytesread++;
			
			//parse the rest of the bytes in the message if need be
			while (Serial.available() > 0) {
				_MIDIByte = byte(Serial.read());

				//stop parsing when we hit another status byte
				if (_MIDIByte >= 0x80) break;

				//add to our buffer
				bytesread++;
				_MIDIAddToBuffer(_MIDIByte);
			}
		}
	}

	//return the number of read bytes
	return bytesread;
}
