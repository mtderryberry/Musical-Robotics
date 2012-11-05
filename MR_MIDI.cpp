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
	cli();//stop interrupts
	//prevent segfults
	if (_MIDI_buffer_queue_size - 1 < MR_MIDI_BUFFERSIZE) {
		//we have room in our buffer
		_MIDI_buffer[++_MIDI_buffer_queue_size] = input;
	}
	sei();//allow interrupts
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

		//make sure we're getting a status message
		if (Serial.peek() >= 0x80) return 0;

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
				//stop parsing when we hit another status byte
				if (Serial.peek() >= 0x80) break;

				//add to our buffer as it's more data that we need
				_MIDIByte = byte(Serial.read());
				bytesread++;
				_MIDIAddToBuffer(_MIDIByte);
			}
		}
	}

	//return the number of read bytes
	return bytesread;
}

/*========================================
 FUNCTION:	_getByteFromMIDIQueue
 USAGE:		Grabs the next byte in the MIDI queue
 RETURNS:	byte from queue.
 ========================================*/
byte _getByteFromMIDIQueue() {
	cli();//stop interrupts
	byte tmp = _MIDI_buffer[0];
	//shift everything down
	int i;
	for (i=0; i < _MIDI_buffer_queue_size - 1; i++) {
		_MIDI_buffer[i] = _MIDI_buffer[i+1];
	}
	//lower our queue pointer
	if (_MIDI_buffer_queue_size > 0) _MIDI_buffer_queue_size--;
	sei();//allow interrupts
	return tmp;
}

/*========================================
 FUNCTION:	isSystemMIDI
 USAGE:		Checks if MIDI byte is data or message
 RETURNS:	boolean if it is system.
 ========================================*/
bool isSystemMIDI(byte input) {
	return input >= 0x80;
}

/*========================================
 FUNCTION:	getNextMIDICommand
 USAGE:		returns the next MIDI message in teh queue
 or null if no messages exist.
 RETURNS:	MIDIConnamd object
 ========================================*/
MIDIConnamd getNextMIDICommand() {
	//check if we have anything in our buffer
	if(_MIDI_buffer[0]==null) return null;

	//make a temporary MIDICommand object
	MIDIConnamd tmp;
	
	cli();//stop interrupts
	
	//We should always get a system message as our first byte
	//but in case not, here is our erro checking
	while (!isSystemMIDI(_MIDI_buffer[0])) _getByteFromMIDIQueue(); // remove the first item from the queue

	//well we should have fixed the issue if there was one
	//but let's make sure we accidentally didn't erase everything
	if(_MIDI_buffer[0]==null) return null;

	//good we made it this far, so we have a valid MIDI command in our buffer

	//try parsing our midi command
	tmp.type = MR_MIDI_ERROR; //this is for starters

	byte cmdByte = 0xF0 & _getByteFromMIDIQueue();//our first command byte with channel bits stripped

	//parse the byte into a character

	if (cmdByte == MR_MIDI_SYS_NOTE_OFF) tmp.type = 'f';
	else if (cmdByte == MR_MIDI_SYS_NOTE_ON) tmp.type = 'o';
	else if (cmdByte == MR_MIDI_SYS_CONTROL_CHANGE) tmp.type = 'c';
	
	//depeding on the type of message, look for more bytes
	


	sei();//allow interrupts
	return tmp;
}
