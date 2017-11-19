#include <wire.h>;

#include "RTClib.h";

RTC_DS1307 rtc;

#include <Wire.h>

#include <SoftwareSerial.h>

#include "rgb_lcd.h"

rgb_lcd rgbLcd;


void setup() {
  if (! rtc.begin()) {
    while (1);
  }
  if (! rtc.isrunning()) {
    rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  rgbLcd.begin(16,2);

}

void loop() {
  DateTime now = rtc.now();
  rgbLcd.setCursor(0,0);
  rgbLcd.print((String(now.day()) + String("/") + String(now.month()) + String("/") + String(now.year())));
  rgbLcd.setCursor(0,1);
  rgbLcd.print((String(now.hour()) + String(":") + String(now.minute()) + String(":") + String(now.second())));
  delay(1000);

}
