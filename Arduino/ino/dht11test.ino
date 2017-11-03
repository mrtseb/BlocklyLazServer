#include <Wire.h>
#include <SoftwareSerial.h>

#include "TSSerial.h"
#include "rgb_lcd.h"
#include "DHT.h"

#include "Arduino.h"
void setup();
void loop();
void _delay(float seconds);
void _loop();
#line 9
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double temp;
double hum;
double sol;
double capteur;
DHT dht(4, 11);
rgb_lcd rgbLcd;
TSSerial bt;



void setup(){
    rgbLcd.begin(16,2);
    
    pinMode(0,INPUT);
    pinMode(2,OUTPUT);
}

void loop(){
    
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    sol = analogRead(0);
    rgbLcd.setCursor(0,0);
    rgbLcd.print(String("T:")+dht.readTemperature()+String(" H:")+dht.readHumidity());
    rgbLcd.setCursor(0,1);
    rgbLcd.print(String("SOL:")+analogRead(0));
    if(((bt.dataAvailable(5))==(1))){
        capteur = bt.receiveVariable("C", 5);
        if(((capteur)==(1))){
        bt.send(5, String("TEMP")+":"+temp);}
        if(((capteur)==(2))){
        bt.send(5, String("HUM")+":"+hum);}
        if(((capteur)==(3))){
        bt.send(5, String("SOL")+":"+sol);}
    }
    if((sol) < (500)){
        digitalWrite(2,1);
        _delay(1);
        digitalWrite(2,0);
        _delay(1);
    }
    _delay(1);
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}


