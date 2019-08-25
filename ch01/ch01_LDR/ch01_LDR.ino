const int sensorPin = A0;    // connect sensor to analog input 0

// Low and high values for the sensor readings. You may need to adjust these.
const int low  = 200;
const int high = 800;

// the next two lines set the min and max delay between blinks
const int minDuration = 100;  // minimum wait between blinks
const int maxDuration = 1000;  // maximum wait between blinks

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);  // enable output on the led pin
  Serial.begin(9600);            // initialize Serial

}

void loop()
{
  int rate = analogRead(sensorPin);    // read the analog input
  // the next line scales the blink rate between the min and max values
  rate = map(rate, low,high, minDuration,maxDuration); // convert blink rate
  rate = constrain(rate, minDuration,maxDuration);     // constrain the value         
  
  Serial.println(rate);            // print rate to serial monitor
  digitalWrite(LED_BUILTIN, HIGH); // set the LED on
  delay(rate);                     // wait duration dependent on light level
  digitalWrite(LED_BUILTIN, LOW);  // set the LED off
  delay(rate);
}
