#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=89.33341217041016,162.33334350585938
AudioEffectEnvelope      envelope1;      //xy=259.3333511352539,160.33334350585938
AudioEffectDelay         delay1;         //xy=456.3333740234375,433.33336639404297
AudioMixer4              feedbackMixer;         //xy=460.3333740234375,235.33335971832275
AudioMixer4              sumBusMixer;         //xy=714.333381652832,176.33336639404297
AudioOutputI2S           i2s1;           //xy=912.3333854675293,179.33335876464844
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(envelope1, 0, sumBusMixer, 0);
AudioConnection          patchCord3(envelope1, 0, feedbackMixer, 0);
AudioConnection          patchCord4(delay1, 0, feedbackMixer, 1);
AudioConnection          patchCord5(delay1, 0, sumBusMixer, 1);
AudioConnection          patchCord6(feedbackMixer, delay1);
AudioConnection          patchCord7(sumBusMixer, 0, i2s1, 0);
AudioConnection          patchCord8(sumBusMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=192.3333625793457,55.33339977264404
// GUItool: end automatically generated code




void setup() {

  // audio memory
  AudioMemory(120);

  // init audio shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);


  feedbackMixer.gain(0, 1.0);
  feedbackMixer.gain(1, 0.5);

  waveform1.begin(0.3, 440, WAVEFORM_SINE);

  
  //envelope settings
  envelope1.delay(5);
  envelope1.attack(15);
  
  //delay settings
  delay1.delay(0, 75);


}


void loop() {
  envelope1.noteOn();
  delay(50);
  envelope1.noteOff();
  delay(2000);
  
}




