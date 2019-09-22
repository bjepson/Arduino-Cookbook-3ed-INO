/*
   Arduino 101 Bluetooth and IMU demo
*/

#include <CurieBLE.h>
#include <CurieIMU.h>

BLEService ledService("19B10010-E8F2-537E-4F6C-D104768A1214"); //create svc


// create switch characteristic and allow remote device to read and write
BLECharCharacteristic
ledCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214",
                  BLERead | BLEWrite);
// create button characteristic and allow remote device notifications
BLECharCharacteristic
buttonCharacteristic("19B10012-E8F2-537E-4F6C-D104768A1214",
                     BLERead | BLENotify); // allows remote device to get notifications

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // use the onboard LED as an output

  // begin initialization
  BLE.begin();

  // set the local name peripheral advertises
  BLE.setLocalName("BtnLED");
  // set the UUID for the service this peripheral advertises:
  BLE.setAdvertisedService(ledService);

  // add the characteristics to the service
  ledService.addCharacteristic(ledCharacteristic);
  ledService.addCharacteristic(buttonCharacteristic);

  // add the service
  BLE.addService(ledService);

  ledCharacteristic.setValue(0);
  buttonCharacteristic.setValue(0);

  // start advertising
  BLE.advertise();
  while(!Serial);
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  Serial.println(".");
  BLE.poll();   // poll BLE peripheral

  bool buttonValue = isMotionDetected();
  // has the value changed since the last read
  bool buttonChanged = (buttonCharacteristic.value() != buttonValue);

  if (buttonChanged) {
    // button state changed, update characteristics
    ledCharacteristic.setValue(buttonValue);
    buttonCharacteristic.setValue(buttonValue);
  }

  if (ledCharacteristic.written() ) {
    // update LED, central has written to characteristic
    if (ledCharacteristic.value()) {
      Serial.println("LED on");
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      Serial.println("LED off");
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

// return true if motion detected
bool isMotionDetected(void) {
  if (CurieIMU.motionDetected(Z_AXIS, POSITIVE) ||
      CurieIMU.motionDetected(Z_AXIS, NEGATIVE)) {
    Serial.println("Motion detected on Z-axis");
    return true;
  }
  return false;
}
