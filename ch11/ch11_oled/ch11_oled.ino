/*
 * OLED SSD13xx sketch
 * Display text and a moving ball on an OLED display.
 */

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 128
#define HEIGHT 32

#define OLED_DC     8
#define OLED_CS    10
#define OLED_RESET  9
Adafruit_SSD1306 display(WIDTH, HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

#define MODE SSD1306_SWITCHCAPVCC // get display voltage from 3.3V internally

void setup() 
{
  Serial.begin(9600);
  if(!display.begin(MODE)) 
  {
    Serial.println("Could not initialize display");
    while(1); // halt
  }

  showAndScroll("Small",  1);
  showAndScroll("Medium", 2);
  showAndScroll("Large",  3);
}

// Show text and scroll it briefly
void showAndScroll(String text, int textSize) 
{
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0); // Move the cursor to 0,0
  display.clearDisplay();  // clear the screen
  
  display.setTextSize(textSize);
  display.println(text);
  display.display();

  // Scroll the display right for 3 seconds
  display.startscrollright(0x00, 0x0F);
  delay(3000);
  display.stopscroll();
}

int ballDir = 1;            // Current direction of motion
int ballDiameter = 8;       // Diameter
int ballX = ballDiameter;   // Starting X position
int ballY = ballDiameter*2; // Y position
void loop() 
{
  display.clearDisplay();
  
  // If the ball is approaching the edge of the screen, reverse direction
  if (ballX >= WIDTH - ballDiameter || ballX < ballDiameter) 
  {
    ballDir *= -1;
  }

  // Move the ball's X position
  ballX += ballDir;

  // Draw a ball
  display.fillCircle(ballX, ballY, ballDiameter/2, SSD1306_INVERSE);
  display.display();
  delay(25);
  
  // Erase the ball
  display.fillCircle(ballX, ballY, ballDiameter/2, SSD1306_INVERSE);
  display.display();
}
