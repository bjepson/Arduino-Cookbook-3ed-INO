#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 128
#define HEIGHT 32

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(WIDTH, HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

//#define OLED_DC     6
//#define OLED_CS     7
//#define OLED_RESET  8
//Adafruit_SSD1306 display(WIDTH, HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

#define MODE SSD1306_SWITCHCAPVCC // get display voltage from 3.3V internally

void setup() {
  Serial.begin(9600);

  if(!display.begin(MODE)) {
    Serial.println("Could not initialize display");
    while(1); // halt
  }

  showAndScroll("Small",  1);
  showAndScroll("Medium", 2);
  showAndScroll("Large",  3);
}

void loop() {
}


void showAndScroll(String text, int textSize) {
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);
  display.clearDisplay();
  display.setTextSize(textSize);
  display.println(text);
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(3000);
  display.stopscroll();
}
