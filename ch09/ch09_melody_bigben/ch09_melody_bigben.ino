/*
 * The Chimes of Big Ben
 * Speaker is connected to digital pin 9
 * Be seeing you!
 */

const int speakerPin = 9; // connect speaker to pin 9

char noteNames[] = {'B', 'E','F','G'};
unsigned int frequencies[] = {247,330,370,415};
const byte noteCount = sizeof(noteNames); // number of notes (7 here)

char score[] = "EGFB EFGE GEFB BFGE";  
const byte scoreLen = sizeof(score); // the number of notes in the score

void setup()
{
}

void loop()
{
  for (int i = 0; i < scoreLen; i++)
  {
    int duration = 1000;  // each note lasts for a third of a second
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
