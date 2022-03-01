// Example of simple 8-Voice polyphinic synth 
// demo shows voice allocation and envelope triggering.
// This version uses arrays of object for more concise code.

#include "USBHost_t36.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
// I put the waveformMod and envelope objects into 
// arrays in this example to show how much easier 
// the voice allocation is using for loops

AudioSynthWaveformModulated waveformMod[8];   //xy=173,331
AudioEffectEnvelope      envelope[8];      //xy=341,197
AudioMixer4              mixer1;         //xy=543,280
AudioMixer4              mixer2;         //xy=548,457
AudioMixer4              mixer3;         //xy=717,354
AudioOutputI2S           i2s1;           //xy=904,356
AudioConnection          patchCord1(waveformMod[0], envelope[0]);
AudioConnection          patchCord2(waveformMod[1], envelope[1]);
AudioConnection          patchCord3(waveformMod[2], envelope[2]);
AudioConnection          patchCord4(waveformMod[3], envelope[3]);
AudioConnection          patchCord5(waveformMod[4], envelope[4]);
AudioConnection          patchCord6(waveformMod[5], envelope[5]);
AudioConnection          patchCord7(waveformMod[6], envelope[6]);
AudioConnection          patchCord8(waveformMod[7], envelope[7]);
AudioConnection          patchCord9(envelope[0], 0, mixer1, 0);
AudioConnection          patchCord10(envelope[1], 0, mixer1, 1);
AudioConnection          patchCord11(envelope[2], 0, mixer1, 3);
AudioConnection          patchCord12(envelope[3], 0, mixer1, 2);
AudioConnection          patchCord13(envelope[4], 0, mixer2, 0);
AudioConnection          patchCord14(envelope[5], 0, mixer2, 2);
AudioConnection          patchCord15(envelope[6], 0, mixer2, 1);
AudioConnection          patchCord16(envelope[7], 0, mixer2, 3);
AudioConnection          patchCord17(mixer1, 0, mixer3, 0);
AudioConnection          patchCord18(mixer2, 0, mixer3, 1);
AudioConnection          patchCord19(mixer3, 0, i2s1, 0);
AudioConnection          patchCord20(mixer3, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=910,405
// GUItool: end automatically generated code

int voice_allocation[8];

USBHost myusb;
MIDIDevice midi1(myusb);

void setup() {
  
  AudioMemory(30);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);


  for(int i=0;i<8;i++) {
    
    voice_allocation[i] = -1;
    
    waveformMod[i].begin(WAVEFORM_SQUARE);
    waveformMod[i].amplitude(.4);

    envelope[i].delay(0);
    envelope[i].attack(20);
    envelope[i].hold(0);
    envelope[i].decay(200);
    envelope[i].sustain(.2);
    envelope[i].release(250);
    
  }

  mixer1.gain(0, 0.7);
  mixer1.gain(1, 0.7);
  mixer1.gain(2, 0.7);
  mixer1.gain(3, 0.7);
  
  mixer2.gain(0, 0.7);
  mixer2.gain(1, 0.7);
  mixer2.gain(2, 0.7);
  mixer2.gain(3, 0.7);

  mixer3.gain(0, 0.8);
  mixer3.gain(1, 0.8);
  mixer3.gain(2, 0.0);
  mixer3.gain(3, 0.0); 

   
  myusb.begin();
  midi1.setHandleNoteOff(OnNoteOff);
  midi1.setHandleNoteOn(OnNoteOn);
  midi1.setHandleControlChange(OnControlChange);

  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleControlChange(OnControlChange);

}

void loop() {

  //read MIDI messages from USB host and regular USB MIDI
  myusb.Task();
  midi1.read();
  
  usbMIDI.read();

}

void OnNoteOn(byte channel, byte note, byte velocity) {

  // first convert MIDI note and velocity to frequency and amplitude
  float freq = 440 * pow(2, ((note-69)/12.f));
  float amp = velocity /127.f;
  
  //The next step is to find a free 'voice' (oscillator/envelope pair)
  int voice = -1;
  voice = get_free_voice();
  
  //then send the frequency and amplitude to that voice, trigger the
  //envelope noteOn() and set the voice_allocation value to the note
  //for looking up the noteOff trigger
  if(voice!=-1) {
    waveformMod[voice].frequency(freq);
    waveformMod[voice].amplitude(amp);
    envelope[voice].noteOn();
    voice_allocation[voice] = note;
    } 
}

void OnNoteOff(byte channel, byte note, byte velocity) {
    // first find which voice is playing that MIDI note
    int voice = -1;
    for (int i=0;i<8;i++) {
      if(voice_allocation[i]==note) voice = i;
    }
  
  if(voice!=-1) {
    envelope[voice].noteOff();
    voice_allocation[voice] = -1;
  } 
  
}
void OnControlChange(byte channel, byte control, byte value) {

  //maybe something here to change envelope settings
  //using cc messages?
}

int get_free_voice() {
  
  //step through the voice_allocation array starting at the beginning
  //and return the first one that has -1, meaning its not being used
  for (int i=0;i<8;i++){
    if (voice_allocation[i]==-1) return i;
  }
  return -1;
}
