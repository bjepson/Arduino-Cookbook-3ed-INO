/* microphone sketch
 * SparkFun breakout board for Electret Microphone is connected to analog pin 0
 */

const int micPin = A0;            // Microphone connected to analog 0
const int ledPin = LED_BUILTIN;   // the code will flash the built-in LED
const int middleValue = 512;      // the middle of the range of analog values
const int numberOfSamples = 128;  // how many readings will be taken each time

int sample;                       // the value read from microphone each time
long signal;                      // the reading once you have removed DC offset
long newReading;                  // the average of that loop of readings

long runningAverage = 0;          // the running average of calculated values
const int averagedOver = 16;      // how quickly new values affect running average
                                  // bigger numbers mean slower

const int threshold = 30;        // at what level the light turns on

void setup() 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  long sumOfSquares = 0;
  for (int i=0; i<numberOfSamples; i++) { // take many readings and average them
    sample = analogRead(micPin);          // take a reading
    signal = (sample - middleValue);      // work out its offset from the center
    signal *= signal;                     // square it to make all values positive
    sumOfSquares += signal;               // add to the total
  }

  newReading = sqrt(sumOfSquares/numberOfSamples);

  // calculate running average
  runningAverage=(((averagedOver-1)*runningAverage)+newReading)/averagedOver;

  Serial.print("new:"); Serial.print(20*log10(newReading));
  Serial.print(",");
  Serial.print("running:"); Serial.println(20*log10(runningAverage));

  if (runningAverage>threshold){         // is average more than the threshold ?
    digitalWrite(ledPin, HIGH);          // if it is turn on the LED
  }else{
    digitalWrite(ledPin, LOW);           // if it isn't turn the LED off
  }

}
