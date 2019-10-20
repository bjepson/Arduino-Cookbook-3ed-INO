/*
  IR_remote_detector sketch
  An IR remote receiver is connected to pin 2.
  The built-in LED toggles each time a button on the remote is pressed.
 */

#include <IRremote.h>           // adds the library code to the sketch

const int irReceiverPin = 2;    // pin the receiver is connected to
const int ledPin = LED_BUILTIN;

IRrecv irrecv(irReceiverPin);   // create an IRrecv object
decode_results decodedSignal;   // stores results from IR detector

void setup()
{
  pinMode(ledPin, OUTPUT);
  irrecv.enableIRIn();          // Start the receiver object
  Serial.begin(9600);
}

int lightState = LOW;          // keep track of whether the LED is on
unsigned long last = millis();  // remember when we last received an IR message

void loop()
{
  if (irrecv.decode(&decodedSignal) == true) // this is true if a message has
                                             // been received
  {
    if (millis() - last > 250) {       // has it been 1/4 sec since last message?
      Serial.println(decodedSignal.value);
      if (lightState == LOW)
        lightState = HIGH;
      else
        lightState = LOW;
      digitalWrite(ledPin, lightState);
    }
    last = millis();
    irrecv.resume();                         // watch out for another message
  }
}
