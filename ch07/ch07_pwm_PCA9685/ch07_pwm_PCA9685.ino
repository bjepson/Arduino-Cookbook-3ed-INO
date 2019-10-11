/*
   PCA9685 sketch
   Create a Knight Rider-like effect on LEDs plugged into all the PCA9685 outputs
   this version assumes one PCA9685 with 16 LEDs
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // assumes default I2C address of 0x40

void setup()
{
  pwm.begin(); // Initialize the PWM board
}

int channel = 0;
int channel_direction = 1;
int intensity = 4095;       // Maximum brightness
int dim = intensity / 4;    // Intensity for a dim LED 
  
void loop()
{
  channel += channel_direction; // increment (or decrement) the channel number
  
  // Turn off all the pins
  for (int pin = 0; pin < 16; pin++) {
    pwm.setPin(pin, 0);
  }

  // If we've hit channel 0, set direction to 1
  if (channel == 0) {
    channel_direction = 1;
  }
  else { // If we're at channel 1 or higher, set its previous neighbor to dim
    pwm.setPin(channel - 1, dim);
  }

  // Set this channel to maximum brightness
  pwm.setPin(channel, intensity);
  
  if (channel < 16) { // If we're below channel 16, set the next channel to dim
    pwm.setPin(channel + 1, dim);
  }
  else { // If we've hit channel 16, set direction to -1
    channel_direction = -1;
  }

  delay(75);
}
