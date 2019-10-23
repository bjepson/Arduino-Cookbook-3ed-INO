/*
 * Dual Tones
 * Plays Twinkle Twinkle Little Star over two octaves.
 */
#include <Tone.h>

int notes1[] = {NOTE_C3, NOTE_C3, NOTE_G3, NOTE_G3, NOTE_A4, NOTE_A4,
                NOTE_G3, NOTE_F3, NOTE_F3, NOTE_E3, NOTE_E3, NOTE_D3,
                NOTE_D3, NOTE_C3 };
int notes2[] = {NOTE_C3, NOTE_C3, NOTE_G3, NOTE_G3, NOTE_A4, NOTE_A4,
                NOTE_G3, NOTE_F3, NOTE_F3, NOTE_E3, NOTE_E3, NOTE_D3,
                NOTE_D3, NOTE_C3 };
const byte scoreLen = sizeof(notes1)/sizeof(notes1[0]); // number of notes

// You can declare the tones as an array
Tone notePlayer[2];

void setup(void)
{
  notePlayer[0].begin(11);
  notePlayer[1].begin(12);
}

void loop(void)
{
  for (int i = 0; i < scoreLen; i++)
  {
    notePlayer[0].play(notes1[i]);
    delay(100); // Slight delay before starting the next note
    notePlayer[1].play(notes2[i]);
    delay(400);
    notePlayer[0].stop();
    notePlayer[1].stop();
    delay(30);
  }
  delay(1000);
}
