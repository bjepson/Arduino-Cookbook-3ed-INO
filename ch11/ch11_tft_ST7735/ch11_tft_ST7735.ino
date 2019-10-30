/*
 * Adafruit GFX ST7735 sketch
 * Display text and a moving ball on the display
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

// Define the connections for your panel. This will vary depending on
// your display and the board you are using
#define TFT_CS   39
#define TFT_RST  37 
#define TFT_DC   38
#define TFT_BACKLIGHT  7
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) 
{
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab packaging
  
  pinMode(TFT_BACKLIGHT, OUTPUT); // Backlight pin
  digitalWrite(TFT_BACKLIGHT, HIGH); // Turn on the backlight
  
  tft.setRotation(2); // This will depend on how you mounted the panel

  tft.fillScreen(ST77XX_BLACK); // Fill the screen with black

  // Display some text in a variety of fonts
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

int ballDir = 1;          // Current direction of motion
int ballDiameter = 8;     // Diameter
int ballX = ballDiameter; // Starting X position
void loop() 
{
  // If the ball is approaching the edge of the screen, reverse direction
  if (ballX >= tft.width() - ballDiameter || ballX < ballDiameter) {
    ballDir *= -1;
  }

  ballX += ballDir; // Move the ball's X position

  // Calculate the Y position based on where the cursor was
  int ballY = tft.getCursorY() + ballDiameter*2;

  tft.fillCircle(ballX, ballY, ballDiameter/2, 0xffff00); // Yellow ball
  delay(25);
  tft.fillCircle(ballX, ballY, ballDiameter/2, 0x000000); // Erase the ball
}
