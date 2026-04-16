#include "Adafruit_TCS34725.h"
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"

SoftwareSerial mySerial(11, 10);
DFRobotDFPlayerMini myDFPlayer;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  if (!tcs.begin()) {
    Serial.println("TCS34725 not found!");
    while (true);
  }
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer not found!");
    while (true);
  }

  myDFPlayer.volume(25);
  delay(2000);

  myDFPlayer.playMp3Folder(6); delay(2500);
  myDFPlayer.playMp3Folder(1); delay(2000);
  myDFPlayer.playMp3Folder(2); delay(2000);
  myDFPlayer.playMp3Folder(3); delay(2000);
  myDFPlayer.playMp3Folder(4); delay(2000);
  myDFPlayer.playMp3Folder(5); delay(2000);
}

void loop() {
  uint16_t r = 0, g = 0, b = 0, c = 0;

  for (int i = 0; i < 5; i++) {
    uint16_t tr, tg, tb, tc;
    tcs.getRawData(&tr, &tg, &tb, &tc);
    r += tr; g += tg; b += tb; c += tc;
    delay(40);
  }
  r /= 5; g /= 5; b /= 5; c /= 5;

  Serial.print("RAW → R:"); Serial.print(r);
  Serial.print(" G:"); Serial.print(g);
  Serial.print(" B:"); Serial.print(b);
  Serial.print(" C:"); Serial.print(c);

  if (c < 50) {
    Serial.println(" → BLACK");
    playTrack(5);
    delay(2200);
    return;
  }

  float red   = (float)r / c * 100.0;
  float green = (float)g / c * 100.0;
  float blue  = (float)b / c * 100.0;

  Serial.print("  NORM → R:"); Serial.print(red, 1);
  Serial.print("% G:"); Serial.print(green, 1);
  Serial.print("% B:"); Serial.print(blue, 1);
  Serial.print("%");

  int track = 0;
  String name = "";

  if (red > 60 && green > 60 && blue > 60) {
    track = 4; name = "WHITE";
  } else if (red < 20 && green < 20 && blue < 20) {
    track = 5; name = "BLACK";
  } else if (red > green && red > blue) {
    track = 1; name = "RED";
  } else if (green > red && green > blue) {
    track = 2; name = "GREEN";
  } else {
    track = 3; name = "BLUE";
  }

  Serial.println(" → " + name);
  playTrack(track);
  delay(2200);
}

void playTrack(int track) {
  myDFPlayer.playMp3Folder(track);
  delay(120);
}
