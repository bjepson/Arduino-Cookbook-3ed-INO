/*
 * Charlieplexing sketch
 * light six LEDs in sequence that are connected to pins 2, 3, and 4
 */

int pins[] = {2,3,4};  // the pins that are connected to LEDs

// the next two lines infer number of pins and LEDs from the above array
const int NUMBER_OF_PINS = sizeof(pins)/ sizeof(pins[0]);
const int NUMBER_OF_LEDS = NUMBER_OF_PINS * (NUMBER_OF_PINS-1);

byte pairs[NUMBER_OF_LEDS/2][2] = { {2,1}, {1,0}, {2,0} }; // maps pins to LEDs


void setup()
{
   // nothing needed here
}

void loop(){
    for(int i=0; i < NUMBER_OF_LEDS; i++)
    {
       lightLed(i);  // light each LED in turn
       delay(1000);
    }
}


// this function lights the given LED, the first LED is 0
void lightLed(int led)
{
  // the following four lines convert LED number to pin numbers
  int indexA = pairs[led/2][0];
  int indexB = pairs[led/2][1];
  int pinA = pins[indexA];
  int pinB = pins[indexB];

  // turn off all pins not connected to the given LED
  for(int i=0; i < NUMBER_OF_PINS; i++)
    if( pins[i] != pinA && pins[i] != pinB)
    {  // if this pin is not one of our pins
        pinMode(pins[i], INPUT);   // set the mode to input
        digitalWrite(pins[i],LOW); // make sure pull-up is off
    }
  // now turn on the pins for the given LED
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  if( led % 2 == 0)
  {
     digitalWrite(pinA,LOW);
     digitalWrite(pinB,HIGH);
  }
  else
  {
     digitalWrite(pinB,LOW);
     digitalWrite(pinA,HIGH);
  }
}
