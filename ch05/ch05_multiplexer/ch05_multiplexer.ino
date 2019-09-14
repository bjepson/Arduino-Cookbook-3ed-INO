/*
 * multiplexer sketch
 * read 1 of 8 analog values into single analog input pin with 4051 multiplexer
 */

// array of pins used to select 1 of 8 inputs on multiplexer
const int select[] = {2,3,4}; // pins connected to the 4051 input select lines
const int analogPin = A0;      // the analog pin connected to multiplexer output

// this function returns the analog value for the given channel
int getValue(int channel)
{
   // set the selector pins HIGH and LOW to match the binary value of channel
   for(int bit = 0; bit < 3; bit++)
   {
      int pin = select[bit]; // the pin wired to the multiplexer select bit
      int isBitSet =  bitRead(channel, bit); // true if given bit set in channel
      digitalWrite(pin, isBitSet);
   }
   return analogRead(analogPin);
}

void setup()
{
  for(int bit = 0; bit < 3; bit++)
  {
    pinMode(select[bit], OUTPUT);  // set the three select pins to output
  }
  Serial.begin(9600);
}
void loop () {
  // print the values for each channel once per second
  for(int channel = 0; channel < 8; channel++)
  {
     int value = getValue(channel);
     Serial.print("Channel ");
     Serial.print(channel);
     Serial.print(" = ");
     Serial.println(value);
  }
  delay (1000);
}
