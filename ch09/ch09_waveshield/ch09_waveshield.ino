/*
 * WaveShieldPlaySelection sketch
 * play a selected WAV file
 * Position of variable resistor slider when button pressed selects file to play
 */

#include <FatReader.h>
#include <SdReader.h>

#include "WaveHC.h"
#include "WaveUtil.h"

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
FatReader file;   // This object represents the WAV file
WaveHC wave;      // Only wave (audio) object - only one file played at a time

const int buttonPin = A1;
const int potPin    = A0;

char * wavFiles[] = {
"1.WAV","2.WAV","3.WAV","4.WAV","5.WAV","6.WAV","7.WAV","8.WAV","9.WAV"};

/*
 * Define macro to put error messages in flash memory
 */
#define error(msg) error_P(PSTR(msg))

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);

  if (!card.init())
  {
    // Something went wrong, sdErrorCheck prints an error number
    error("Card init. failed!"); 
  }

  // enable optimized read - some cards may time out
  card.partialBlockRead(true);

  // find a FAT partition
  uint8_t part;
  for (part = 0; part < 5; part++)      // we have up to 5 slots to look in
  {
    if (vol.init(card, part))
      break;                            // found one so break out of this for loop
  }
  if (part == 5)                        // valid parts are 0 to 4, more not valid
  {
    error("No valid FAT partition!");
  }

  // tell the user about what we found
  Serial.print("Using partition ");
  Serial.print(part, DEC);
  Serial.print(", type is FAT");
  Serial.println(vol.fatType(),DEC);     // FAT16 or FAT32?

  // Try to open the root directory
  if (!root.openRoot(vol))
  {
    error("Can't open root dir!"); // Something went wrong,
  }

  // if here then all the file prep succeeded.
  Serial.println("Ready!");
}

void loop()
{
  if(digitalRead(buttonPin) == LOW)
  {
    int value = analogRead(potPin);
    int index = map(value,0,1023,0,8); // index into one of the 9 files
    playcomplete(wavFiles[index]);
    Serial.println(value);
  }
}

// Plays a full file from beginning to end with no pause.
void playcomplete(char *name)
{
  // call playfile find and play this name
  playfile(name);

  int n = 0;
  // playing occurs in interrupts; print dots to show we're running
  while (wave.isplaying) { 
    Serial.print(".");
    if (!(++n % 32))Serial.println(); // newline every 32 dots
    delay(100);
  }

  while (wave.isplaying) {
    // do nothing while it's playing
  }
  // now it's done playing
}

void playfile(char *name) {
  // see if the wave object is currently doing something
  if (wave.isplaying) { 
  // already playing something, so stop it!
    wave.stop(); // stop it
  }
  // look in the root directory and open the file
  if (!file.open(root, name)) {
    Serial.print("Couldn't open file ");
    Serial.print(name);
    return;
  }
  // read the file and turn it into a wave object
  if (!wave.create(file)) {
    Serial.println("Not a valid WAV");
    return;
  }
  Serial.print("Playing file "); 
  Serial.println(name);
  // start playback
  wave.play();
}

void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

/*
 * print error message and halt
 */
void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}
