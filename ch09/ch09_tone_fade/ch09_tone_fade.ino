/*
 * Tone and fade sketch
 * Plays tones while fading an LED
 */
byte speakerPin = 9;
byte ledPin = 3;

void setup()
{
  pinMode(speakerPin, OUTPUT);
}

void playTone(int period, int duration)
{
  // period is one cycle of tone
  // duration is how long the pulsing should last in milliseconds
  int pulse = period / 2;
  for (long i = 0; i < duration * 1000L; i += period )
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(pulse);
  }
}

void fadeLED(){
  // These two static variables are assigned initial values
  // only the first time the function is called.
  static int brightness = 0;
  static int changeval  = 5;

  analogWrite(ledPin, brightness);

  // If we've exceeded the limits of analogWrite
  brightness += changeval;
  if (brightness >= 255 || brightness <= 0)
    changeval *= -1; // Change direction

  delay(2);
}

void loop()
{
  // a note with period of 15289 is deep C (second lowest C note on piano)
  for(int period=15289; period >= 477;  period=period / 2)  // play 6 octaves
  {
    playTone(period, 200); // play tone for 200 milliseconds
    fadeLED();
  }
}
