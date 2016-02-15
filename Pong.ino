#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>

//calib
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define RADIUS 29
#define RADIUSOUTER 30
int keyOld = -1;
bool gameover = false;
bool playing = false;
String pin = String();
bool menuopen = true;
int lastp1x = 0, lastp2x = 0, lastp1y = 0, lastp2y = 0;


void setup(void) {

  Serial.begin(9600);

  tft.begin();

  tft.setRotation(2);
  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  Serial.println("Touchscreen Initiated");

  tft.fillScreen(ILI9341_BLACK);
  printstartscreen();
}

void loop() {
  while (menuopen == true) {
    checkmenu();
  }
  startsequence();
  while (playing == true) {
    playgame();
  }
}

void printstartscreen() {
  //  tft.fillRect(10, 20, 50, 10, ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(32, 58);
  //tft.print("1");
  //  tft.fillRect(60, 290, 50, 10, ILI9341_WHITE);
  tft.setCursor(10, 100);
  tft.print("Wanna Play A Game?");
  tft.drawRoundRect(60, 150, 110, 50, 10, ILI9341_WHITE);
  tft.setCursor(100, 170);
  tft.print("Go!");
}

void checkmenu() {
  TS_Point p = ts.getPoint();
  int xCoord = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
  int yCoord = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
  if ((xCoord > 60) && (xCoord < 170) && (yCoord > 150) && (yCoord < 200))
    menuopen = false;
  else
    menuopen = true;
}

void startsequence()
{
  Serial.println("Game is starting");
  tft.fillRect(5, 30, 220, 200, ILI9341_BLACK);
  tft.setTextSize(5);
  for (int loadnum = 3; loadnum > 0; loadnum--) {
    tft.setCursor(110, 140);
    tft.print(loadnum);
    delay(600);
    tft.fillRect(110, 140, 40, 40, ILI9341_BLACK);
  }
  tft.setCursor(90, 140);
  tft.print("Go!");
  delay(600);
  tft.fillRect(90, 140, 80, 40, ILI9341_BLACK);
  playing = true;
}

void playgame()
{
  Serial.println("started");
  //delay(500);
  //draw ball
  //some kinda loop to get ball position
  //paddle interaction with ball
  int score = 0, oldx = 110, oldy = 140, newx = 110, newy = 140;
  int xcoornew = 0, xcoorold = 0;
  while (score < 80) {
    newx = oldx + 3;
    newy = oldy + 5;
    tft.fillRect(oldx, oldy, 15, 15, ILI9341_BLACK);
    tft.fillRect(newx, newy, 15, 15, ILI9341_WHITE);
    oldx = newx;
    oldy = newy;
    TS_Point p;
    while (! ts.bufferEmpty())  {
      p = ts.getPoint();
    }
    xcoornew = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    tft.fillRect((xcoorold-30), 290, 50, 10, ILI9341_BLACK);    //old data
    tft.fillRect((xcoornew-30), 290, 50, 10, ILI9341_WHITE);   //new data
    Serial.println(xcoornew);
    xcoorold = xcoornew;    
    updatepaddleai();
    delay(25);
    score++;
  }
}

void updatepaddleh() {

}
void updatepaddleai() {

}


