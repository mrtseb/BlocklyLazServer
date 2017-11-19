#include <Wire.h>
#include <SoftwareSerial.h>
#include "RTClib.h"
#include "rgb_lcd.h"

RTC_DS1307 RTC;
rgb_lcd rgbLcd;

void setup() {
  rgbLcd.begin(16,2);
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");

    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {
  DateTime now = RTC.now();
  rgbLcd.setCursor(0,0);
  rgbLcd.print(String(now.day())+"/"+String(now.month())+"/"+String(now.year()));
  rgbLcd.setCursor(0,1);
  rgbLcd.print("                ");
  rgbLcd.setCursor(0,1);
  rgbLcd.print(String(now.hour())+":"+String(now.minute())+":"+String(now.second()));
  delay(1000);

}

