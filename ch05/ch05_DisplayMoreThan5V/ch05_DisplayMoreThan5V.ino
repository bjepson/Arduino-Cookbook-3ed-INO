/*
  DisplayMoreThan5V sketch
  prints the voltage on analog pin to the serial port
  Do not connect more than 5 volts directly to an Arduino pin.
*/

const float referenceVolts = 5;      // the default reference on a 5-volt board
//const float referenceVolts = 3.3;  // use this for a 3.3-volt board

const float R1 = 1000; // value for a maximum voltage of 10 volts
const float R2 = 1000;
// determine by voltage divider resistors, see text
const float resistorFactor = 1023.0 * (R2/(R1 + R2));  
const int batteryPin = 0; // +V from battery is connected to analog pin 0

void setup()
{
   Serial.begin(9600);
}

void loop()
{
   int val = analogRead(batteryPin);  // read the value from the sensor
   float volts = (val / resistorFactor) * referenceVolts; // calculate the ratio
   Serial.println(volts);  // print the value in volts
}
