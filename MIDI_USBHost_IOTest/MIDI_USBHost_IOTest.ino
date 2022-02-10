// Simple test of USB Host, send and receive MIDI.
// Incoming MIDI note messages light up LED 13
// And generate an outgoing note message back through 
// the USB interface.
// 
//

#include "USBHost_t36.h"

USBHost myusb;
MIDIDevice midi1(myusb);

int led = 13;

void setup()
{
	myusb.begin();
	midi1.setHandleNoteOff(OnNoteOff);
	midi1.setHandleNoteOn(OnNoteOn);
  midi1.setHandleControlChange(OnControlChange);
  pinMode(led, OUTPUT);
}


void loop()
{
	myusb.Task();
	midi1.read();

}

void OnNoteOn(byte channel, byte note, byte velocity)
{
  midi1.sendNoteOn(note+8,velocity, 1);
  digitalWrite(led, HIGH);
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
   midi1.sendNoteOff(note+8,0, 1);
   digitalWrite(led, LOW);
}

void OnControlChange(byte channel, byte control, byte value)
{
   //I remember reading somwhere that you have to include a CC function
   //even if you don't do anything...?
}
