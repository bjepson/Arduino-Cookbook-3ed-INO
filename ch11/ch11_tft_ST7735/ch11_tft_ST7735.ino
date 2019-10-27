#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#define TFT_CS   39
#define TFT_RST  37 
#define TFT_DC   38
#define TFT_BACKLIGHT  7 // Display backlight pin

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  
  Serial.begin(9600);

  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on
  tft.setRotation(90);

  tft.fillScreen(ST77XX_BLACK);

  // large block of text
  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(0, 0);
  tft.setTextWrap(false);

  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Small");

  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("Medium");

  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(3);
  tft.println("Large");

}

int ballDir = 1;
int ballDiameter = 8;
int ballX = ballDiameter/2;
void loop() {

  if (ballX >= tft.width() - ballDiameter || ballX < ballDiameter/2) {
    ballDir *= -1;
  }
  ballX += ballDir;
  int ballY = tft.getCursorY() + ballDiameter*2;

  tft.fillCircle(ballX, ballY, ballDiameter/2, 0xffff00);
  delay(25);
  tft.fillCircle(ballX, ballY, ballDiameter/2, 0x000000);

}
