//
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
  //this creates the USB connection for the teensy as Host device
  myusb.begin();
  //and these are the message handlers for the MIDI messages coming
  //from the USB device connected to the pins on the top of the teensy
  midi1.setHandleNoteOn(OnNoteOn);
  midi1.setHandleNoteOff(OnNoteOff);
  midi1.setHandleControlChange(OnControlChange);

  // make sure you select USB Type-> MIDI in the tools menu
  // so that you can make the teensy act as a MIDI client as well
  // These message handlers deal with MIDI messages coming from
  // the USB connection on the side of the teensy (micro port)
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleControlChange(OnControlChange);

  
  pinMode(led, OUTPUT);
}


void loop()
{
  myusb.Task();
  // we have to read both MIDI interfaces
  midi1.read();
  usbMIDI.read();
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
