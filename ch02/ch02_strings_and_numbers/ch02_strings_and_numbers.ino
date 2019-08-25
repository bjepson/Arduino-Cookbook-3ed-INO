/*
   NumberToString
   Creates a string from a given number
*/

char buffer[12];  // long data type has 11 characters (including the
// minus sign) and a terminating nullvoid loop()

void setup()
{
  Serial.begin(9600);
  while (!Serial); // Needed for Leonardo and SAMD boards

  emit1();
  emit2();

  int number = 12;
  number += 1;
  Serial.println(number);

  String textNumber = "12";
  textNumber += 1;
  Serial.println(textNumber);

  long value = 12345;
  ltoa(value, buffer, 10);

  Serial.print( value);
  Serial.print(" has  ");
  Serial.print(strlen(buffer));
  Serial.println(" digits");

  value = 123456789;
  ltoa(value, buffer, 10);

  Serial.print( value);
  Serial.print(" has  ");
  Serial.print(strlen(buffer));
  Serial.println(" digits");
}

void loop()
{
}

void emit1() {
  int value = 127;
  String myReadout = "The reading was ";
  myReadout.concat(value);
  Serial.println(myReadout);

}

void emit2()
{
  int value = 127;
  String myReadout = "The reading was ";
  myReadout += value;
  Serial.println(myReadout);

}
