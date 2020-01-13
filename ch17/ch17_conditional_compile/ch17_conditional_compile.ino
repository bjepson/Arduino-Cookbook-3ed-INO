/*
 * ConditionalCompile sketch
 * This sketch recognizes the controller chip using conditional defines
 */

int numberOfSensors;
int val = 0;               // variable to store the value coming from the sensor

void setup()
{
  Serial.begin(9600);

#if defined(__AVR_ATmega2560__)   // defined when selecting Mega in the IDE
  numberOfSensors = 16;           // the number of analog inputs on the Mega
  #pragma message ( "Using 16 sensors" )
#else                             // if not Mega then assume a standard board
  numberOfSensors = 6;            // analog inputs on a standard Arduino board
  #pragma message ( "Using 6 sensors" )
#endif

  Serial.print("The number of sensors is ");
  Serial.println(numberOfSensors);
}

void loop() {
  for(int sensor = 0; sensor < numberOfSensors; sensor++)
  {
    val = analogRead(sensor);    // read the sensor value
    Serial.print(sensor); Serial.print(": ");
    Serial.println(val);         // display the value
  }
  Serial.println();
  delay(1000);        // delay a second between readings
}
