/*
 * Twinkle sketch
 * Plays "Twinkle, Twinkle Little Star"
 * Speaker is connected to digital pin 9
 */

const int speakerPin = 9; // connect speaker to pin 9

char noteNames[] = {'C','D','E','F','G','a','b'};
unsigned int frequencies[] = {262,294,330,349,392,440,494};
const byte noteCount = sizeof(noteNames); // number of notes (7 here)

//notes, a space represents a rest
char score[] = "CCGGaaGFFEEDDC GGFFEEDGGFFEED CCGGaaGFFEEDDC ";  
const byte scoreLen = sizeof(score); // the number of notes in the score

byte beats[scoreLen] = {1,1,1,1,1,1,2,  1,1,1,1,1,1,2,1,
                        1,1,1,1,1,1,2,  1,1,1,1,1,1,2,1,
                        1,1,1,1,1,1,2,  1,1,1,1,1,1,2};
byte beat = 180; // beats per minute for eighth notes
unsigned int speed = 60000 / beat; // the time in ms for one beat

void setup()
{
}

void loop()
{
  for (int i = 0; i < scoreLen; i++)
  {
    int duration = beats[i] * speed; // use beats array to determine duration
    playNote(score[i], duration); // play the note
    delay(duration/10); // slight pause to separate the notes
  }

  delay(4000); // wait four seconds before repeating the song
}

void playNote(char note, int duration)
{
  // play the tone corresponding to the note name
  for (int i = 0; i < noteCount; i++)
  {
    // try and find a match for the noteName to get the index to the note
    if (noteNames[i] == note) // find a matching note name in the array
      tone(speakerPin, frequencies[i], duration); //  play the note
  }
  // if there is no match then the note is a rest, so just do the delay
  delay(duration);
}
