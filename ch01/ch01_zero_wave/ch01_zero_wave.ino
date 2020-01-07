/*
 * Zero wave sketch
 */
const int outputPin = A0; // headphones connected to analog 0
const int sensorPin = A1; // connect sensor to analog input 1

const int low  = 200;
const int high = 800;

const int sampleCount = 16;  // number of samples used to render one cycle

const int minDur = 1000000/(sampleCount*500); // period in uS for 500 Hz
const int maxDur = 1000000/(sampleCount*50);  // period for 50 hz

// table of values for 16 samples of one sine wave cycle
static int sinewave[sampleCount] = { 
  0x1FF,0x2B6,0x355,0x3C7,0x3FF,0x3C7,0x355,0x2B6,
  0x1FF,0x148,0x0A9,0x037,0x000,0x037,0x0A9,0x148 
};
  
void setup()
{
  analogWriteResolution(10); // set the Arduino DAC resolution to maximum
}

void loop()
{
  int sensorReading = analogRead(sensorPin);    // read the analog input
  int duration = map(sensorReading, low, high, minDur, maxDur);
  duration = constrain(duration, minDur, maxDur);

  for(int sample=0; sample < sampleCount; sample++) {
    analogWrite(outputPin, sinewave[sample]);
    delayMicroseconds(duration);
  }
}
