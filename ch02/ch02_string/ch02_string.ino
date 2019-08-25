/*
  Basic_Strings sketch
 */

String text1 = "This string";
String text2 = " has more text";
String text3;  // to be assigned within the sketch

void setup()
{
  Serial.begin(9600);
  while(!Serial); // See #serial_output_begin_wait

  Serial.print( text1);
  Serial.print(" is ");
  Serial.print(text1.length());
  Serial.println(" characters long.");

  Serial.print("text2 is ");
  Serial.print(text2.length());
  Serial.println(" characters long.");

  text1.concat(text2);
  Serial.println("text1 now contains: ");
  Serial.println(text1);
}

void loop()
{
}
