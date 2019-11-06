#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SdFat.h>
#include <Adafruit_ImageReader.h>

#define SD_CS   4
#define TFT_CS 10
#define TFT_DC  9

// Create the objects for each of the SPI devices
SdFat SD;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

SdFile root;
Adafruit_ImageReader reader(SD);

void setup(void) 
{
  Serial.begin(9600);

  tft.begin(); // Initialize the TFT
  
  if(!SD.begin(SD_CS, SD_SCK_MHZ(25))) 
  { 
    Serial.println("Could not initialize SD card");
    while(1); // halt
  }

  if (!root.open("/")) 
  {
    Serial.println("Could not read SD card directory");
    while(1); // halt
  }
}

void loop() 
{
  ImageReturnCode rc;
  SdFile file;
  char filename[256];

  while (file.openNext(&root, O_RDONLY)) 
  {
    file.getName(filename, sizeof(filename)/ sizeof(filename[0]));
    if(isBMP(filename))
    {
      tft.fillScreen(0);
      rc = reader.drawBMP(filename, tft, 0, 0);
      delay(2000);
    }
    file.close();
  }
  root.rewind();
}

int isBMP(char fname[])
{
    String fn = String(fname);
    fn.toLowerCase();
    return fn.endsWith("bmp");
}
