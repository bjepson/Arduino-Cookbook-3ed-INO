const int outputPin = A0;    // headphones connected to analog 0
const int sensorPin = A1;    // connect sensor to analog input 1

const int low  = 200;
const int high = 800;

const int sampleCount = 16;  // number of samples used to render one cycle

const int minDur = 1000000/(sampleCount*500); // period in uS for 500 Hz
const int maxDur = 1000000/(sampleCount*50);  // period for 50 hz

// table of values for 16 samples of one sine wave cycle
static int sinewave[sampleCount] = { 
  0x7FF,0xADD,0xDA7,0xF4D,0xFFF,0xF77,0xDA7,0xB40,
  0x7FF,0x521,0x257,0xB1, 0x0,  0x87, 0x257,0x4BE 
};
  
void setup()
{
  //pinMode(outputPin, OUTPUT);   // enable output on the led pin
  analogWriteResolution(12);    // set the Arduino DAC resolution
  analogWrite(outputPin, 0);
}

void loop()
{
  int sensorReading = analogRead(sensorPin);    // read the analog input
  int duration = map(sensorReading, low,high, minDur,maxDur);
  duration = constrain(duration, minDur,maxDur);    // constrain the value
  for(int sample=0; sample < sampleCount; sample++) {
    analogWrite(outputPin, sinewave[sample]);
    delayMicroseconds(duration);
  }
}
