/*
midiOut sketch
sends MIDI messages to play a scale on a MIDI instrument
each time the switch on pin 2 is pressed
*/

//these numbers specify which note
const byte notes[8] = {60, 62, 64, 65, 67, 69, 71, 72}; 
//they are part of the MIDI specification
const int length = 8;
const int switchPin = 2;
const int ledPin = 13;

void setup() {
  Serial.begin(31250);
  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (digitalRead(switchPin) == LOW)
  {
    for (byte noteNumber = 0; noteNumber < 8; noteNumber++)
    {
      playMidiNote(1, notes[noteNumber], 127);
      digitalWrite(ledPin, HIGH);
      delay(500);
      playMidiNote(1, notes[noteNumber], 0);
      digitalWrite(ledPin, HIGH);
      delay(50);
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
