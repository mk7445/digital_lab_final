#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=210,108.33334827423096
AudioEffectEnvelope      envelope1;      //xy=212.33336639404297,215.33334922790527
AudioFilterBiquad        filter;        //xy=354.3333549499512,215.33331775665283
AudioEffectGranular      granular1;      //xy=434.33338928222656,320.33335304260254
AudioEffectDelay         delay1;         //xy=641.3333892822266,522.3333740234375
AudioMixer4              feedbackMixer;         //xy=653.3333969116211,329.3333377838135
AudioMixer4              sumBusMixer;         //xy=940.9999542236328,226.3333511352539
AudioOutputI2S           i2s1;           //xy=1114.3333282470703,227.33336544036865
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(envelope1, filter);
AudioConnection          patchCord3(filter, granular1);
AudioConnection          patchCord4(filter, 0, sumBusMixer, 0);
AudioConnection          patchCord5(granular1, 0, feedbackMixer, 0);
AudioConnection          patchCord6(delay1, 0, feedbackMixer, 1);
AudioConnection          patchCord7(feedbackMixer, delay1);
AudioConnection          patchCord8(feedbackMixer, 0, sumBusMixer, 1);
AudioConnection          patchCord9(sumBusMixer, 0, i2s1, 0);
AudioConnection          patchCord10(sumBusMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=192.3333625793457,55.33339977264404
// GUItool: end automatically generated code




#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];


//knobs, switches, etc.
float feedbackKnob = 0.00;
int delayTimeKnob = 0;
int grainSizeKnob = 0;
float grainPitchKnob = 0.0;


void setup() {

  // audio memory
  AudioMemory(120);

  // init audio shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  sumBusMixer.gain(0, 1.0);

  //interal processing setup
  feedbackMixer.gain(0, 1.0);
  feedbackMixer.gain(1, 0.0); //starts feedback at 0%



  //test tone settings
  waveform1.begin(0.2, 440, WAVEFORM_SINE);

  envelope1.delay(0);
  envelope1.attack(30);

  filter.setLowpass(0, 7000, 1);
  
  //delay settings
  delay1.delay(0, 0);

  //granular settings
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  granular1.setSpeed(1.0);

  //for testing
  Serial.begin(9600);


}


void loop() {

  checkFeedback();
  checkDelayTime();
  checkGrainSize();
  checkGrainPitch();
  playNote();
  
  // checkAudioMemory();

}

void playNote() {

  envelope1.noteOn();
  delay(4000);
  envelope1.noteOff();
  delay(2000);
}

//---------------------------------
void checkFeedback() {
  feedbackKnob = analogRead(A14) / 1023.0;
  map(feedbackKnob, 0.00, 1.00, 0.00, 0.60);
  // Serial.println(feedbackKnob);
  feedbackMixer.gain(1, feedbackKnob);
}

void checkDelayTime() {
  delayTimeKnob = map(analogRead(A15), 0, 1023, 50, 150);   //sets range of delay times in milliseconds
  //Serial.println(delayTimeKnob);
  delay1.delay(0, delayTimeKnob);
}

//checks grain size pot
void checkGrainSize() {
  grainSizeKnob = map(analogRead(A16), 0, 1023, 50, 200);
  granular1.beginFreeze(grainSizeKnob);
}

void checkGrainPitch() {
  grainPitchKnob = analogRead(A17) / 1023.0;
  grainPitchKnob = map(grainPitchKnob, 0.000, 1.000, 0.0, 12.0); //divides into 12TET
  grainPitchKnob = map(grainPitchKnob, 0.0, 12.0, 1.000, 2.000); //maps over an octave (ratio of 2x speed of original frequency)
  Serial.println(grainPitchKnob);
  granular1.setSpeed(grainPitchKnob);
}
//---------------------------------

void checkAudioMemory() {
  // Serial.println(delayTimeKnob);
  //Serial.println(grainSizeKnob);
  Serial.println(AudioMemoryUsage());
  Serial.println("\t");

  //Serial.println(AudioMemoryUsageMax());
}





