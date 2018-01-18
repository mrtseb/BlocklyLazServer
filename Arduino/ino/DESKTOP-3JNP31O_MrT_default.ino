#include <wire.h>;

#include "RTClib.h";

RTC_DS1307 rtc;

DateTime now;

DateTime depart;


void setup() {
  if (! rtc.begin()) {
    while (1);
  }
  if (! rtc.isrunning()) {
    rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  else {
    depart = rtc.now();
  }

  pinMode(2, OUTPUT);
}

void loop() {
  DateTime now = rtc.now();
  now = rtc.now();
  if ((now.unixtime() - depart.unixtime()) % (180) == 0) {
    digitalWrite(2,HIGH);
    delay(60000);
    digitalWrite(2,LOW);
  }

}
