/*
 * Two SPI Device sketch
 * Loads all the bitmaps on the attached SD card
 * and displays them on a TFT screen.
 */

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SdFat.h>
#include <Adafruit_ImageReader.h>

#define SD_CS   4 // Chip select for SD reader
#define TFT_CS 10 // Chip select for TFT
#define TFT_DC  9 // Data/command pin for TFT
#define TFT_RST 8 // Reset pin for TFT

// Create the objects for each of the SPI devices
SdFat SD;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

SdFile root; // Root directory of SD card
Adafruit_ImageReader reader(SD); // Object to load and display images

void setup(void) 
{
  Serial.begin(9600);
  if(!SD.begin(SD_CS, SD_SCK_MHZ(25))) // Start the SD card reader at 25MHz
  { 
    Serial.println("Could not initialize SD card");
    while(1); // halt
  }
  tft.begin(); // Initialize the TFT

  if (!root.open("/")) 
  {
    Serial.println("Could not read SD card directory");
    while(1); // halt
  }
}

void loop() 
{
  ImageReturnCode rc; // Return code from image operations
  SdFile file; // Current file
  char filename[256]; // Buffer for filename

  while (file.openNext(&root, O_RDONLY)) // Find the next file on the SD card
  {
    file.getName(filename, sizeof(filename)/ sizeof(filename[0]));
    if(isBMP(filename)) // If it's a BMP, display it on the TFT
    {
      tft.fillScreen(0);
      rc = reader.drawBMP(filename, tft, 0, 0);
      delay(2000); // Pause
    }
    file.close();
  }
  root.rewind(); // Go back to the first file in the root directory
}

// Determins whether a file is a bitmap (BMP) file
int isBMP(char fname[])
{
  String fn = String(fname);
  fn.toLowerCase();
  return fn.endsWith("bmp");
}
