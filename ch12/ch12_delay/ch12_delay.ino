/*
 * delay sketch
 */

const unsigned long oneSecond = 1000;  // a second is a thousand milliseconds
const unsigned long oneMinute = oneSecond * 60;
const unsigned long oneHour   = oneMinute * 60;
const unsigned long oneDay    = oneHour * 24;

void setup()
{
  Serial.begin(9600);
  while(!Serial); // Needed on Leonardo and ARM-based boards
}

void loop()
{
  Serial.println("delay for 1 millisecond");
  delay(1);
  Serial.println("delay for 1 second");
  delay(oneSecond);
  Serial.println("delay for 1 minute");
  delay(oneMinute);
  Serial.println("delay for 1 hour");
  delay(oneHour);
  Serial.println("delay for 1 day");
  delay(oneDay);
  Serial.println("Ready to start over");
}
