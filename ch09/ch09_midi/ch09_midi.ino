/*
 * midiOut sketch
 * Sends MIDI messages to play a scale on a MIDI instrument
 * each time the switch on pin 2 is pressed
*/

// these numbers specify which note to play
const byte notes[8] = {60, 62, 64, 65, 67, 69, 71, 72}; 
const int num_notes = sizeof(notes)/ sizeof(notes[0]);;

const int switchPin = 2;
const int ledPin = LED_BUILTIN;

void setup() {
  Serial.begin(31250);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (digitalRead(switchPin) == LOW)
  {
    for (byte noteNumber = 0; noteNumber < num_notes; noteNumber++)
    {
      // Play the note
      playMidiNote(1, notes[noteNumber], 127);
      digitalWrite(ledPin, HIGH);
      delay(70); // Hold the note

      // Stop playing the note (velocity of 0)
      playMidiNote(1, notes[noteNumber], 0);
      digitalWrite(ledPin, HIGH);
      delay(30);
    }
  }
}

void playMidiNote(byte channel, byte note, byte velocity)
{
  byte midiMessage= 0x90 + (channel - 1);
  Serial.write(midiMessage);
  Serial.write(note);
  Serial.write(velocity);
}
