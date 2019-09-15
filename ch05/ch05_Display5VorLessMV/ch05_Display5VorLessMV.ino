const int batteryPin = A0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  long val = analogRead(batteryPin);   // read the value from the sensor -
                                       // note val is a long int
  Serial.println( (val * (500000/1023L)) / 100);  // print the value in millivolts
}
