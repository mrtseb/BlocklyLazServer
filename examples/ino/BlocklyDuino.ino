#include "DHT.h"

#include <Wire.h>

#include <SoftwareSerial.h>

#include "rgb_lcd.h"

int in1;

int in2;

int temp;

int hum;

DHT dht4(4, 11);

rgb_lcd rgbLcd;

void setup()
{
  pinMode(5, OUTPUT);
  pinMode(4, INPUT);
  rgbLcd.begin(16,2);

}


void loop()
{
  in1 = analogRead(A0);
  in2 = analogRead(A3);
  if (temp < 20) {
    digitalWrite(5,HIGH);

  } else {
    digitalWrite(5,LOW);

  }
  temp = dht4.readTemperature();
  hum = dht4.readHumidity();
  rgbLcd.setCursor(0,0);
  rgbLcd.print(String(String("T:")+temp)+" oC");
  rgbLcd.setCursor(0,1);
  rgbLcd.print(String(String("H:")+hum)+" %");
  delay(500);

}
