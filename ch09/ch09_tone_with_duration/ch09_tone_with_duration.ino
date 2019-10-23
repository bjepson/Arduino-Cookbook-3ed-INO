const int speakerPin = 9;    // connect speaker to pin 9
const int pitchPin = A0;     // input that determines frequency of the tone
const int durationPin = A1;  // input that will determine the duration of the tone

void setup()
{
}

void loop()
{
  int sensor0Reading = analogRead(pitchPin);    // read input for frequency
  int sensor1Reading = analogRead(durationPin); // read input for duration

  // map the analog readings to a meaningful range
  int frequency  = map(sensor0Reading, 0, 1023, 100, 5000); // 100Hz to 5kHz
  int duration = map(sensor1Reading, 0, 1023, 100, 1000);   // dur 0.1-1 second
  tone(speakerPin, frequency, duration); // play the tone
  delay(duration); // wait for the tone to finish
}
