void setup() {
  Serial.begin(9600);
  int myValue0 =  20 % 10;  // get the modulus(remainder) of 20 divided by 10
  Serial.println(myValue0);
  int myValue1 =  21 % 10;  // get the modulus(remainder) of 21 divided by 10
  Serial.println(myValue1);
  // put your setup code here, to run once:

}

void printOffsetHour( int hourNow, int offsetHours)
{
   Serial.println((hourNow + offsetHours) % 24);
}

void loop() {
  for (int myValue = 0; myValue <= 100; myValue += 5)
  {
    if (myValue % 10 == 0)
    {
      Serial.println("The value is a multiple of 10");
    }
  }
  delay(5000);
  for (int myValue = 0; myValue <= 10; myValue++)
  {
    if (myValue % 2 == 0)
    {
      Serial.println("The value is even");
    }
    else
    {
      Serial.println("The value is odd");
    }
  }
  delay(5000);
}
