/*
 * Tone sketch
 *
 * Plays tones through a speaker on digital pin 9
 * Frequency determined by values read from analog pin
 */

const int speakerPin = 9;    // connect speaker to pin 9
const int pitchPin = A0;     // pot that will determine the frequency of the tone

void setup()
{
}

void loop()
{
  int sensor0Reading = analogRead(pitchPin);    // read input to set frequency

  // map the analog readings to a meaningful range
  int frequency  = map(sensor0Reading, 0, 1023, 100, 5000); // 100Hz to 5kHz

  int duration = 250;   // how long the tone lasts
  tone(speakerPin, frequency, duration); // play the tone
  delay(1000); // pause one second
}
