/*
 * nunchuck_lines sketch
 * sends data to Processing to draw line that follows nunchuck movement
 */

#include <Wire.h> // initialize wire

const int vccPin = A3;   // +v provided by pin 17
const int gndPin = A2;   // gnd provided by pin 16

const int dataLength = 6;          // number of bytes to request
static byte rawData[dataLength];   // array to store nunchuck data

enum nunchuckItems { joyX, joyY, accelX, accelY, accelZ, btnZ, btnC };

void setup() {  
  pinMode(gndPin, OUTPUT); // set power pins to the correct state
  pinMode(vccPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  digitalWrite(vccPin, HIGH);
  delay(100);  // wait for things to stabilize        

  Serial.begin(9600);
  Serial.println("OK");
  nunchuckInit();
  Serial.println("OK");
}

void loop(){
  nunchuckRead();
  int acceleration = getValue(accelX);
  if((acceleration >= 75) && (acceleration <= 185))
  {
    //map returns a value from 0 to 63 for values from 75 to 185
    byte  x = map(acceleration, 75, 185, 0, 63);
    Serial.write(x);
  delay(20); // the time in milliseconds between redraws
  }
}

void nunchuckInit(){
  Wire.begin();                // join i2c bus as master
  Wire.beginTransmission(0x52);// transmit to device 0x52
  Wire.write((byte)0x40);      // sends memory address
  Wire.write((byte)0x00);      // sends sent a zero.  
  Wire.endTransmission();      // stop transmitting
}

// Send a request for data to the nunchuck
static void nunchuckRequest(){
  Wire.beginTransmission(0x52);// transmit to device 0x52
  Wire.write((byte)0x00);      // sends one byte
  Wire.endTransmission();      // stop transmitting
}

// Receive data back from the nunchuck, 
// returns true if read successful, else false
bool nunchuckRead(){
  int cnt=0;
  Wire.requestFrom (0x52, dataLength); // request data from nunchuck
  while (Wire.available ()) {
    rawData[cnt] = nunchuckDecode(Wire.read());
    cnt++;
  }
  nunchuckRequest();  // send request for next data payload
  if (cnt >= dataLength) 
    return true;     // success if all 6 bytes received
  else
    return false;    //failure
}

// Encode data to format that most wiimote drivers accept
static char nunchuckDecode (byte x) {
  return (x ^ 0x17) + 0x17;
}

int getValue(int item){
  if (item <= accelZ)
    return (int)rawData[item]; 
  else if (item  == btnZ) 
    return bitRead(rawData[5], 0) ? 0: 1;
  else if (item  == btnC) 
    return bitRead(rawData[5], 1) ? 0: 1;    
}
