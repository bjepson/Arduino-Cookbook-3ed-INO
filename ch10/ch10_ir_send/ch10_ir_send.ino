/*
 * irSend sketch
 * this code needs an IR LED connected to pin 3
 * and 5 switches connected to pins 6 - 10
 */

#include <IRremote.h>       // IR remote control library

const int numberOfKeys = 5;
const int firstKey = 6;   // the first pin of the 5 sequential pins connected 
                          // to buttons
bool buttonState[numberOfKeys];
bool lastButtonState[numberOfKeys];
long irKeyCodes[numberOfKeys] = {
  0x18E758A7,  //0 key
  0x18E708F7,  //1 key
  0x18E78877,  //2 key
  0x18E748B7,  //3 key
  0x18E7C837,  //4 key
};

IRsend irsend;

void setup()
{
  for (int i = 0; i < numberOfKeys; i++) {
    buttonState[i] = true;
    lastButtonState[i] = true;
    int physicalPin=i + firstKey;
    pinMode(physicalPin, INPUT_PULLUP);  // turn on pull-ups
  }
  Serial.begin(9600);
}

void loop() {
  for (int keyNumber=0; keyNumber<numberOfKeys; keyNumber++)
  {
    int physicalPinToRead = keyNumber + firstKey;
    buttonState[keyNumber] = digitalRead(physicalPinToRead);
    if (buttonState[keyNumber] != lastButtonState[keyNumber])
    {
      if (buttonState[keyNumber] == LOW)
      {
        irsend.sendSony(irKeyCodes[keyNumber], 32);
        Serial.println("Sending");
      }
      lastButtonState[keyNumber] = buttonState[keyNumber];
    }
  }
}
