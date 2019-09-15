const int batteryPin = A0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int val = analogRead(batteryPin); // read the value from the sensor
 
  long mv =  (val * (500000/1023L)) / 100; // calculate the value in millivolts
  Serial.print(mv/1000); // print the integer portion of the voltage  
  Serial.print('.');
  int fraction = (mv % 1000); // calculate the fraction
  if (fraction == 0)
  {
     Serial.print("000");       // add three zeros
  }
  else if (fraction < 10)  // if fractional < 10 the 0 is ignored giving a wrong 
                           // time, so add the zeros
  {
     Serial.print("00");       // add two zeros
  }
  else if (fraction < 100)
  {
     Serial.print("0");
  } 
  Serial.println(fraction); // print the fraction
}
