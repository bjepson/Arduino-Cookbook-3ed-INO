/*
 * u8g2 oled sketch
 * Draw some text, move a ball.
 */
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

#define OLED_DC     8
#define OLED_CS    10
#define OLED_RESET  9
U8G2_SSD1306_128X32_UNIVISION_2_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RESET);

u8g2_uint_t displayWidth;

void setup(void) 
{
  u8g2.begin();
  u8g2.setFontPosTop();
  displayWidth = u8g2.getDisplayWidth();

  showAndScroll("Small",  u8g2_font_6x10_tf);
  showAndScroll("Medium", u8g2_font_9x15_tf);
  showAndScroll("Large",  u8g2_font_10x20_tf);
}

int ballDir = 1;          // Current direction of motion
int ballRadius = 4;       // Radius
int ballX = ballRadius*2; // Starting X position
int ballY = ballRadius*4; // Y position
void loop(void) 
{
  u8g2.firstPage(); // picture loop
  do 
  {
    // If the ball is approaching the edge of the screen, reverse direction
    if (ballX >= displayWidth - ballRadius*2 || ballX < ballRadius*2) 
    {
      ballDir *= -1;
    }

    ballX += ballDir; // Move the ball's X position
    u8g2.drawDisc(ballX, ballY, ballRadius); // Draw the ball
  } while ( u8g2.nextPage() );
  delay(25);
}

void showAndScroll(String text, uint8_t *font) 
{
  for (int i = 0; i < 20; i++)
  {
    u8g2.firstPage(); // picture loop
    do
    {
      u8g2.setFont(font);
      u8g2.drawStr(10 + i, 10, text.c_str());
    } while ( u8g2.nextPage() );
    delay(125);
  }
}
