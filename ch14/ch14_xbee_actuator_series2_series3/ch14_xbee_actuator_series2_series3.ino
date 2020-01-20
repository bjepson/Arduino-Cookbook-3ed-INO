/*
  XBeeActuate sketch
  Send a Remote AT command to activate a digital pin on another XBee.
 */

// Uncomment only one of the following
#define MYSERIAL Serial // Uno, Nano, and other AVR boards
//#define MYSERIAL Serial1 // Nano Every, Uno WiFi R2, Leonardo, and ARM boards

const byte frameStartByte = 0x7E;
const byte frameTypeRemoteAT  = 0x17;
const byte remoteATOptionApplyChanges = 0x02;

void setup() 
{
  MYSERIAL.begin(9600);
}

void loop()
{
  toggleRemotePin(1);
  delay(2000);
  toggleRemotePin(0);
  delay(2000);
}

byte sendByte(byte value) 
{
  MYSERIAL.write(value);
  return value;
}

void toggleRemotePin(int value) // 0 = off, nonzero = on
{  
  byte pin_state;
  if (value) 
  {
    pin_state = 0x5;
  } 
  else 
  {
    pin_state = 0x4;
  }

  sendByte(frameStartByte); // Begin the API frame

  // High and low parts of the frame length (not counting checksum)
  sendByte(0x0);
  sendByte(0x10);

  long sum = 0; // Accumulate the checksum

  sum += sendByte(frameTypeRemoteAT); // Indicate this frame contains a
                                      // Remote AT command

  sum += sendByte(0x0);  // frame ID set to zero for no reply

  // The following 8 bytes indicate the ID of the recipient.
  // Use 0xFFFF to broadcast to all nodes.
  sum += sendByte(0x0);
  sum += sendByte(0x0);
  sum += sendByte(0x0);
  sum += sendByte(0x0);
  sum += sendByte(0x0);
  sum += sendByte(0x0);
  sum += sendByte(0xFF);
  sum += sendByte(0xFF);

  // The following 2 bytes indicate the 16-bit address of the recipient.
  // Use 0xFFFE to broadcast to all nodes.
  sum += sendByte(0xFF);
  sum += sendByte(0xFF);

  sum += sendByte(remoteATOptionApplyChanges); // send Remote AT options

  // The text of the AT command
  sum += sendByte('D');
  sum += sendByte('1');

  // The value (0x4 for off, 0x5 for on)
  sum += sendByte(pin_state);

  // Send the checksum
  sendByte( 0xFF - ( sum & 0xFF));

  delay(10); // Pause to let the microcontroller settle down if needed
}
