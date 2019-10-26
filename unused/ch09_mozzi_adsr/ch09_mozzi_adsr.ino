/*  Example playing a sinewave at a set frequency,
    using Mozzi sonification library.

    Demonstrates the use of Oscil to play a wavetable.

    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
    check the README or http://sensorium.github.com/Mozzi/

    Mozzi documentation/API
    https://sensorium.github.io/Mozzi/doc/html/index.html

    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Tim Barrass 2012, CC by-nc-sa.
*/

char noteNames[]    = {'B', 'C', 'D', 'E', 'F', 'G', 'e'};
float frequencies[] = {246.94, 261.63, 293.66, 329.63, 369.99, 415.30, 164.81};
const byte noteCount = sizeof(noteNames) / sizeof(noteNames[0]); // number of notes

char score[] = "EGFB EFGE GEFB BFGE E E E E";
const byte scoreLen = sizeof(score) / sizeof(score[0]); // the number of notes in the score

byte beats[scoreLen] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                        2, 2, 2, 2, 10, 4, 4, 4, 4, 4, 4, 4
                       };
byte beat = 180; // beats per minute for eighth notes
unsigned int speed = 60000 / beat; // the time in ms for one beat

int curr_note = 0;

#include <ADSR.h>
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <EventDelay.h>

ADSR <AUDIO_RATE, AUDIO_RATE> envelope;


// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // Hz, powers of 2 are most reliable

EventDelay kChangeNoteDelay;

void setup() {
  startMozzi(CONTROL_RATE); // :)
  kChangeNoteDelay.start();
  Serial.begin(9600);
}

bool resting = false;
float attack = .20;
float decay = .20;
float sustain = .40;
float release_ms = .20;

void updateControl() {
  if (kChangeNoteDelay.ready()) {
    resting = !resting;
    if (resting) {
      aSin.setFreq(0); // set the frequency
      kChangeNoteDelay.set(200); // note duration ms, within resolution of CONTROL_RATE
    } else {


      if (curr_note >= scoreLen) {
        curr_note = 0;
      }
      int duration = beats[curr_note] * speed; // use beats array to determine duration
      kChangeNoteDelay.set(duration); // note duration ms, within resolution of CONTROL_RATE
      char note = score[curr_note];
      float freq = 0.0;
      for (int i = 0; i < noteCount; i++)
      {
        // try and find a match for the noteName to get the index to the note
        if (noteNames[i] == note) { // find a matching note name in the array
          freq = frequencies[i];
        }
      }

      byte attack_level = 1;
      byte decay_level = 255;
      envelope.setADLevels(attack_level, decay_level);
      envelope.setTimes(duration * attack, duration * decay, duration * sustain, duration * release_ms);
      Serial.println(duration * attack);
      envelope.noteOn();
      aSin.setFreq(freq); // set the frequency
      curr_note++;
    }
    kChangeNoteDelay.start();
  }
}

int updateAudio() {
//  return aSin.next();
  envelope.update();
  return (int) (envelope.next() * aSin.next())>>8;
}

void loop() {
  audioHook(); // required here
}
