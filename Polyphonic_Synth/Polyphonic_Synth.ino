// Example of simple 8-Voice polyphinic synth 
// demo shows voice allocation and envelope triggering

#include "USBHost_t36.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformModulated waveformMod4;   //xy=173,331
AudioSynthWaveformModulated waveformMod5;   //xy=173,403
AudioSynthWaveformModulated waveformMod2;   //xy=174,243
AudioSynthWaveformModulated waveformMod1;   //xy=175,197
AudioSynthWaveformModulated waveformMod3;   //xy=175,285
AudioSynthWaveformModulated waveformMod6;   //xy=178,452
AudioSynthWaveformModulated waveformMod7;   //xy=178,503
AudioSynthWaveformModulated waveformMod8;   //xy=180,555
AudioEffectEnvelope      envelope1;      //xy=341,197
AudioEffectEnvelope      envelope2;      //xy=342,243
AudioEffectEnvelope      envelope4;      //xy=345,330
AudioEffectEnvelope      envelope3;      //xy=346,285
AudioEffectEnvelope      envelope5;      //xy=351,403
AudioEffectEnvelope      envelope7;      //xy=351,503
AudioEffectEnvelope      envelope6;      //xy=353,452
AudioEffectEnvelope      envelope8;      //xy=353,554
AudioMixer4              mixer1;         //xy=543,280
AudioMixer4              mixer2;         //xy=548,457
AudioMixer4              mixer3;         //xy=717,354
AudioOutputI2S           i2s1;           //xy=904,356
AudioConnection          patchCord1(waveformMod4, envelope4);
AudioConnection          patchCord2(waveformMod5, envelope5);
AudioConnection          patchCord3(waveformMod2, envelope2);
AudioConnection          patchCord4(waveformMod1, envelope1);
AudioConnection          patchCord5(waveformMod3, envelope3);
AudioConnection          patchCord6(waveformMod6, envelope6);
AudioConnection          patchCord7(waveformMod7, envelope7);
AudioConnection          patchCord8(waveformMod8, envelope8);
AudioConnection          patchCord9(envelope1, 0, mixer1, 0);
AudioConnection          patchCord10(envelope2, 0, mixer1, 1);
AudioConnection          patchCord11(envelope4, 0, mixer1, 3);
AudioConnection          patchCord12(envelope3, 0, mixer1, 2);
AudioConnection          patchCord13(envelope5, 0, mixer2, 0);
AudioConnection          patchCord14(envelope7, 0, mixer2, 2);
AudioConnection          patchCord15(envelope6, 0, mixer2, 1);
AudioConnection          patchCord16(envelope8, 0, mixer2, 3);
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
  sgtl5000_1.volume(0.5); // caution: very loud - use oscilloscope only!

  //for loop to free up all of the voices (set to -1)
  //and set waveform and envelope 
  for(int i=0;i<8;i++) {
    voice_allocation[i] = -1;
  }

  //Becuase the waveform and envelope objects are not in an array
  //we have to set each one, as opposed to using a for loop :(
  waveformMod1.begin(WAVEFORM_SQUARE);
  waveformMod1.amplitude(.4);
  waveformMod2.begin(WAVEFORM_SQUARE);
  waveformMod2.amplitude(.4);   
  waveformMod3.begin(WAVEFORM_SQUARE);
  waveformMod3.amplitude(.4);
  waveformMod4.begin(WAVEFORM_SQUARE);
  waveformMod4.amplitude(.4);
  waveformMod5.begin(WAVEFORM_SQUARE);
  waveformMod5.amplitude(.4);
  waveformMod6.begin(WAVEFORM_SQUARE);
  waveformMod6.amplitude(.4);
  waveformMod7.begin(WAVEFORM_SQUARE);
  waveformMod7.amplitude(.4);
  waveformMod8.begin(WAVEFORM_SQUARE);
  waveformMod8.amplitude(.4);

  //same thing for setting the envelope variables :( 
  envelope1.delay(0);
  envelope1.attack(20);
  envelope1.hold(0);
  envelope1.decay(200);
  envelope1.sustain(.2);
  envelope1.release(250);
  envelope2.delay(0);
  envelope2.attack(20);
  envelope2.hold(0);
  envelope2.decay(200);
  envelope2.sustain(.2);
  envelope2.release(250);
  envelope3.delay(0);
  envelope3.attack(20);
  envelope3.hold(0);
  envelope3.decay(200);
  envelope3.sustain(.2);
  envelope3.release(250);
  envelope4.delay(0);
  envelope4.attack(20);
  envelope4.hold(0);
  envelope4.decay(200);
  envelope4.sustain(.2);
  envelope4.release(250);
  envelope5.delay(0);
  envelope5.attack(20);
  envelope5.hold(0);
  envelope5.decay(200);
  envelope5.sustain(.2);
  envelope5.release(250);
  envelope6.delay(0);
  envelope6.attack(20);
  envelope6.hold(0);
  envelope6.decay(200);
  envelope6.sustain(.2);
  envelope6.release(250);
  envelope7.delay(0);
  envelope7.attack(20);
  envelope7.hold(0);
  envelope7.decay(200);
  envelope7.sustain(.2);
  envelope7.release(250);
  envelope8.delay(0);
  envelope8.attack(20);
  envelope8.hold(0);
  envelope8.decay(200);
  envelope8.sustain(.2);
  envelope8.release(250);

  mixer1.gain(0, 0.0);
  mixer1.gain(1, 0.0);
  mixer1.gain(2, 0.0);
  mixer1.gain(3, 0.0);
  
  mixer2.gain(0, 0.0);
  mixer2.gain(1, 0.0);
  mixer2.gain(2, 0.0);
  mixer2.gain(3, 0.0);

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
  // put your main code here, to run repeatedly:
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
  if(voice!=-1) {
  
  if (voice==0) {
      waveformMod1.frequency(freq);
      mixer1.gain(0, amp);
      envelope1.noteOn();
      voice_allocation[0] = note;
    } else if (voice==1) {
      waveformMod2.frequency(freq);
      mixer1.gain(1, amp);
      envelope2.noteOn();
      voice_allocation[1] = note;
    } else if (voice==2) {
      waveformMod3.frequency(freq);
      mixer1.gain(2, amp);
      envelope3.noteOn();
      voice_allocation[2] = note;
    } else if (voice==3) {
      waveformMod4.frequency(freq);
      mixer1.gain(3, amp);
      envelope4.noteOn();
      voice_allocation[3] = note;
    } else if (voice==4) {
      waveformMod5.frequency(freq);
      mixer2.gain(0, amp);
      envelope5.noteOn();
      voice_allocation[4] = note;
    } else if (voice==5) {
      waveformMod6.frequency(freq);
      mixer2.gain(1, amp);
      envelope6.noteOn();
      voice_allocation[5] = note;
    } else if (voice==6) {
      waveformMod7.frequency(freq);
      mixer2.gain(2, amp);
      envelope7.noteOn();
      voice_allocation[6] = note;
    } else if (voice==7) {
      waveformMod8.frequency(freq);
      mixer2.gain(3, amp);
      envelope8.noteOn();
      voice_allocation[7] = note;
    }
  }
   
}
void OnNoteOff(byte channel, byte note, byte velocity) {
  // first find which voice is playing that MIDI note
  
  if (note == voice_allocation[0]) {
      envelope1.noteOff();
      voice_allocation[0] = -1;
    } else if (note == voice_allocation[1]) {
      envelope2.noteOff();
      voice_allocation[1] = -1;
    } else if (note == voice_allocation[2]) {
      envelope3.noteOff();
      voice_allocation[2] = -1;
    } else if (note == voice_allocation[3]) {
      envelope4.noteOff();
      voice_allocation[3] = -1;
    } else if (note == voice_allocation[4]) {
      envelope5.noteOff();
      voice_allocation[4] = -1;
    } else if (note == voice_allocation[5]) {
      envelope6.noteOff();
      voice_allocation[5] = -1;
    } else if (note == voice_allocation[6]) {
      envelope7.noteOff();
      voice_allocation[6] = -1;
    } else if (note == voice_allocation[7]) {
      envelope8.noteOff();
      voice_allocation[7] = -1;
    }
}
void OnControlChange(byte channel, byte control, byte value) {
}

int get_free_voice() {
  
  //step through the voice_allocation array starting at the beginning
  //and return the first one that has -1, meaning its not being used
  for (int i=0;i<8;i++){
    if (voice_allocation[i]==-1) return i;
  }
  return -1;
}
