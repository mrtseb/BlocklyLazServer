#include "rgb_lcd.h"
rgb_lcd rgbLcd;

#include "DHT.h"

String flux="";

char mode='a';
long port=0;

int a0;
double temp;
double hum;

DHT dht(4, 11);

void _loop() {

}


void _delay(float seconds){
    long endTime = millis() + seconds * 10;
    while(millis() < endTime)_loop();
}



void setup() {
   
   rgbLcd.begin(16,2);
   pinMode(2,OUTPUT);
   Serial.begin(115200);
   Serial.println("‡ l'Ècoute ...");   
   Serial.flush();
}

void loop() {

   hum = dht.readHumidity();
   temp = dht.readTemperature();
   a0 = analogRead(0);

rgbLcd.setCursor(0,0);
    rgbLcd.print("T: ");
    rgbLcd.print(temp);
    rgbLcd.print(" H: ");
    rgbLcd.print(hum);
    rgbLcd.setCursor(0,1);
    rgbLcd.print("S: ");
    rgbLcd.print(a0);


   if (mode =='A') {
       digitalWrite(2, LOW);
   }


   //mode auto
   if (mode=='A' && a0 < 500) {
        digitalWrite(2, HIGH);
        _delay(10);
   }

   while (Serial.available()>0) {
      char data= Serial.read();
      flux += data;
      _delay(1);

      if (data == 'A') {
        mode='A';
        Serial.println('mode auto!');
      }
      if (data == 'a') {
        mode='a';
        Serial.println('mode manuel!');
      }
      if (data == '#') {
        a0 = analogRead(0);
        //Serial.print("a0:");
        Serial.println(a0);
      }

      if (data == 'T') {
        temp = dht.readTemperature();
        //Serial.print("T:");
        Serial.println(temp);
      }

      if (data == 'H') {
        hum = dht.readHumidity();
        //Serial.print("H:");
        Serial.println(hum);
      }

      if (data == 'D') {
        hum = dht.readHumidity();
        temp = dht.readTemperature();
        a0 = analogRead(0);
        Serial.print(hum);
        Serial.print(';');
        Serial.print(temp);
        Serial.print(';');
        Serial.print(a0);
        Serial.println(';');

      }

      if (mode='A' && data == 'P') {
        Serial.println("Arrosage d√©but!");
        digitalWrite(2, HIGH);
      }

      if (mode='A' && data == 'p') {
        Serial.println("Arrosage fin!");
        digitalWrite(2, LOW);
      }

        flux="";
        Serial.flush();


   }
}

