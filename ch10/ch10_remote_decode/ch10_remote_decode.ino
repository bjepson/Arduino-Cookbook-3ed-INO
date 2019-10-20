/*
 * RemoteDecode sketch
 * Infrared remote control signals are decoded to control LED brightness.
 * The values for keys 0-4 are detected and stored when the sketch starts.
 * Key 0 turns the LED off; brightness increases in steps with keys 1-4.
 */

#include <IRremote.h>           // IR remote control library

const int irReceivePin = 2;     // pin connected to IR detector output
const int ledPin       = 9;     // LED is connected to a PWM pin

const int numberOfKeys = 5;     //  5 keys are learned (0 through 4)
long irKeyCodes[numberOfKeys];  // holds the codes for each key

IRrecv irrecv(irReceivePin);    // create the IR library
decode_results results;         // IR data goes here

void setup()
{
  Serial.begin(9600);
  while(!Serial); // Needed for Leonardo and ARM boards
  pinMode(irReceivePin, INPUT);
  pinMode(ledPin, OUTPUT);
  irrecv.enableIRIn();              // Start the IR receiver
  learnKeycodes();                  // learn remote control key  codes
  Serial.println("Press a remote key");
}

void loop()
{
  long key;
  int  brightness;

  if (irrecv.decode(&results))
  {
    // here if data is received
    irrecv.resume();
    key = convertCodeToKey(results.value);
    if(key >= 0)
    {
      Serial.print("Got key ");
      Serial.println(key);
      brightness = map(key, 0,numberOfKeys-1, 0, 255);
      analogWrite(ledPin, brightness);
    }
  }
}

/*
 * get remote control codes
 */
void learnKeycodes()
{
  while(irrecv.decode(&results))   // empty the buffer
    irrecv.resume();
 
  Serial.println("Ready to learn remote codes");
  long prevValue = -1;
  int i=0;
  while(i < numberOfKeys)
  {
    Serial.print("press remote key ");
    Serial.print(i);
    while(true)
    {
      if(irrecv.decode(&results))
      {
        if(results.value != -1 && 
           results.decode_type != UNKNOWN && 
           results.value != prevValue)
        {
          showReceivedData();
          Serial.println(results.value);
          irKeyCodes[i] = results.value;
          i = i + 1;
          prevValue = results.value;
          irrecv.resume(); // Receive the next value
          break;
        }
        irrecv.resume(); // Receive the next value
      }
    }
  }
  Serial.println("Learning complete");
}

/*
 * converts a remote protocol code to a logical key code 
 * (or -1 if no digit received)
 */
int convertCodeToKey(long code)
{
  for(int i=0; i < numberOfKeys; i++)
  {
    if(code == irKeyCodes[i])
    {
      return i; // found the key so return it
    }
  }
  return -1;
}

/*
 * display the protocol type and value
 */
void showReceivedData()
{
  if (results.decode_type == UNKNOWN)
  {
    Serial.println("-Could not decode message");
  }
  else
  {
    if (results.decode_type == NEC) {
      Serial.print("- decoded NEC: ");
    }
    else if (results.decode_type == SONY) {
      Serial.print("- decoded SONY: ");
    }
    else if (results.decode_type == RC5) {
      Serial.print("- decoded RC5: ");
    }
    else if (results.decode_type == RC6) {
      Serial.print("- decoded RC6: ");
    }
    Serial.print("hex value = ");
    Serial.println( results.value, HEX);
  }
}
