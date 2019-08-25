/*
 * SplitSplit sketch
 * split a comma-separated string
 */

String  text = "Peter,Paul,Mary";  // an example string
String  message = text; // holds text not yet split
int     commaPosition;  // the position of the next comma in the string

void setup()
{
  Serial.begin(9600);
  while(!Serial); // See #serial_output_begin_wait

  Serial.println(message);          // show the source string
  do
  {
      commaPosition = message.indexOf(',');
      if(commaPosition != -1)
      {
          Serial.println( message.substring(0,commaPosition));
          message = message.substring(commaPosition+1, message.length());
      }
      else
      {  // here after the last comma is found
         if(message.length() > 0)
           Serial.println(message);  // if there is text after the last comma,
                                     // print it
      }
   }
   while(commaPosition >=0);
}

void loop()
{
}
