
#define SAMPLERATE_HZ 44100
#define AMPLITUDE     ((1<<25)-1)
#define WAV_SIZE      16

char noteNames[]    = {'C','D','E','F','G','a','b'};
float frequencies[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88};
const byte noteCount = sizeof(noteNames)/sizeof(noteNames[0]); // number of notes (7 here)

// notes, a space represents a rest
char score[] = "CCGGaaGFFEEDDC GGFFEEDGGFFEED CCGGaaGFFEEDDC ";  
const byte scoreLen = sizeof(score)/sizeof(score[0]); // the number of notes in the score

byte beats[scoreLen] = {1,1,1,1,1,1,2,  1,1,1,1,1,1,2,1,
                        1,1,1,1,1,1,2,  1,1,1,1,1,1,2,1,
                        1,1,1,1,1,1,2,  1,1,1,1,1,1,2};
byte beat = 180; // beats per minute for eighth notes
unsigned int speed = 60000 / beat; // the time in ms for one beat

int32_t sine[WAV_SIZE] = {0}; // Sine waveform for this score

const int outputPin = A0;

void setup() {

  analogWriteResolution(12); // set the Arduino DAC resolution
  
  // Generate the sine wave.
  generateSine(AMPLITUDE, sine, WAV_SIZE);
  Serial.begin(9600);

}

void loop() {

  for (int i = 0; i < scoreLen; i++)
  {
    int duration = beats[i] * speed; // use beats array to determine duration
    playNote(score[i], (float) duration/1000L); // play the note
    delay(100); // slight pause to separate the notes
  }
  delay(4000); // wait four seconds before repeating the song

}

void playNote(char note, float duration)
{
  Serial.println(duration);
  // play the tone corresponding to the note name
  for (int i = 0; i < noteCount; i++)
  {
    // try and find a match for the noteName to get the index to the note
    if (noteNames[i] == note) { // find a matching note name in the array
      playWave(sine, WAV_SIZE, frequencies[i], duration); // Play the note
    }
  }
  // if there is no match then the note is a rest, so just do the delay
  delay(duration * 1000);
}

// generateSine function from the Adafruit tone_generator sample
// https://github.com/adafruit/Adafruit_ZeroI2S/tree/master/examples/tone_generator
void generateSine(int32_t amplitude, int32_t* buffer, uint16_t length) {
  // Generate a sine wave and store it in the buffer
  for (int i=0; i<length; ++i) {
    buffer[i] = int32_t(float(amplitude)*sin(2.0*PI*(1.0/length)*i));
  }
}

// playwave function from the Adafruit tone_generator sample
// https://github.com/adafruit/Adafruit_ZeroI2S/tree/master/examples/tone_generator
//
void playWave(int32_t* buffer, uint16_t length, float frequency, float seconds) {
  // Calculate how many samples needed for the duration.
  uint32_t iterations = seconds*SAMPLERATE_HZ;

  // Calculate the 'speed' at which we move through the wave.
  float delta = (frequency*length)/float(SAMPLERATE_HZ);

  // Play all the samples.
  for (uint32_t i=0; i<iterations; ++i) {
    // The position within the wave buffer for this moment in time:
    uint16_t pos = uint32_t(i*delta) % length; 
    int32_t sample = buffer[pos];
    analogWrite(outputPin, sample);
  }
}
