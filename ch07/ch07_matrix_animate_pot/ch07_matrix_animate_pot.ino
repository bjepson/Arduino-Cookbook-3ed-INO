/*
 * matrixMpxAnimation sketch
 * animates two heart images to show a beating heart
 */

// the heart images are stored as bitmaps - each bit corresponds to an LED
// a 0 indicates the LED is off, 1 is on
byte bigHeart[] = {
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000};

byte smallHeart[] = {
  B00000000,
  B00000000,
  B00010100,
  B00111110,
  B00111110,
  B00011100,
  B00001000,
  B00000000};

const int columnPins[] = { 2, 3, 4, 5, 6, 7, 8, 9};
const int rowPins[]    = {10,11,12,A1,A2,A3,A4,A5};

void setup() {
  for (int i = 0; i < 8; i++)
  {
    pinMode(rowPins[i], OUTPUT);        // make all the LED pins outputs
    pinMode(columnPins[i], OUTPUT);
    digitalWrite(columnPins[i], HIGH);  // disconnect column pins from Ground
  }
}

void loop() {
  int sensorValue = analogRead(A0);                // read the analog in value
  int pulseRate =  map(sensorValue,0,1023,40,240); // convert to beats / minute
  int pulseDelay = (60000 / pulseRate);  // milliseconds to wait between beats

  show(smallHeart, 80);            // show the small heart image for 100 ms
  show(bigHeart, 160);             // followed by the big heart for 200ms
  delay(pulseDelay);               // show nothing between beats
}

// Show a frame of an image stored in the array pointed to by the image
// parameter. The frame is repeated for the given duration in milliseconds.
void show(byte * image, unsigned long duration)
{
 unsigned long start = millis();            // begin timing the animation
 while (start + duration > millis())        // loop until the duration period has passed
  {
    for(int row = 0; row < 8; row++)
    {
      digitalWrite(rowPins[row], HIGH);          // connect row to +5 volts
      for(int column = 0; column < 8; column++)
      {
        bool pixel = bitRead(image[row],column);
        if(pixel == 1)
        {
          digitalWrite(columnPins[column], LOW);  // connect column to Gnd
        }
        delayMicroseconds(300);                   // a small delay for each LED
        digitalWrite(columnPins[column], HIGH);   // disconnect column from Gnd
      }
      digitalWrite(rowPins[row], LOW);            // disconnect LEDs
    }
  }
}
