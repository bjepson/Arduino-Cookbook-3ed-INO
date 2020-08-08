/*
 * Zero wave sketch
 */
const int outputPin = A0; // headphones connected to analog 0
const int sensorPin = A1; // connect sensor to analog input 1

const int low  = 400;
const int high = 850;

const int sampleCount = 16;  // number of samples used to render one cycle

const int minDur = 1000000/(sampleCount*1760); // period in uS for 1760 Hz (A7)
const int maxDur = 1000000/(sampleCount*440);  // period for 440 Hz (A5)

// table of values for 16 samples of one sine wave cycle
static int sinewave[sampleCount] = { 
  0x1FF,0x2B6,0x355,0x3C7,0x3FF,0x3C7,0x355,0x2B6,
  0x1FF,0x148,0x0A9,0x037,0x000,0x037,0x0A9,0x148 
};
  
void setup()
{
  Serial.begin(9600);
  analogWriteResolution(10); // set the Arduino DAC resolution to maximum
}

void loop()
{
  int sensorReading = analogRead(sensorPin);    // read the analog input
  int duration = map(sensorReading, low, high, minDur, maxDur);
  duration = constrain(duration, minDur, maxDur);

  Serial.println(duration);
  for(int sample=0; sample < sampleCount; sample++) {
    analogWrite(outputPin, sinewave[sample]);
    delayMicroseconds(duration);
  }
}
