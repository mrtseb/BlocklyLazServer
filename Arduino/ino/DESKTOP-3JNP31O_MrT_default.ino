#include <Wire.h>

#include <SoftwareSerial.h>

#include <MeMCore.h>

MeDCMotor motor_9(9);

MeDCMotor motor_10(10);

void _loop(){
}

void _delay(float seconds){
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime)_loop();
}

void move(int direction, int speed)
{
    int leftSpeed = 0;
    int rightSpeed = 0;
    if(direction == 1){
      	leftSpeed = speed;
      	rightSpeed = speed;
    }else if(direction == 2){
      	leftSpeed = -speed;
      	rightSpeed = -speed;
    }else if(direction == 3){
      	leftSpeed = -speed;
      	rightSpeed = speed;
    }else if(direction == 4){
      	leftSpeed = speed;
      	rightSpeed = -speed;
    }
    motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
    motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}

MeRGBLed rgbled_7(7, 7==7?2:4);


void setup() {
}

void loop() {
  _loop();
  rgbled_7.setColor(0,255,0,0);
  rgbled_7.show();
  delay(500);
  rgbled_7.setColor(0,0,255,0);
  rgbled_7.show();
  delay(500);

}
