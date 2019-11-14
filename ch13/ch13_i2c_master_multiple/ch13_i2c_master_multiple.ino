/*
 * I2C Master multiple sketch
 * Sends multiple sensor data to an I2C secondary using print
 */

#include <Wire.h>

const int address = 4;          // address for the communicating devices
const int firstSensorPin = A0;  // first input pin of sequence
const int nbrSensors = 3;       // three sequential pins will be used
int val;                        // variable to store the sensor value

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  Wire.beginTransmission(address); // transmit to device
  Wire.print('H'); // header indicating start of a message
  Wire.print(nbrSensors);

  for (int i = 0; i < nbrSensors; i++) {
    val = analogRead(firstSensorPin + 1);  // read the sensor
    Wire.print(','); // comma separator
    Wire.print(val);  
  }

  Wire.println(); // end of message
  Wire.endTransmission();
  delay(100);
}
