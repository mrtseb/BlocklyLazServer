#ifndef TSRobuno_H
#define TSRobuno_H

#include <Servo.h>

class TSRobuno
{
  public:
  
  static const byte FRONT = 0;
  static const byte FORWARD = 0;
  static const byte BACK = 1;
  static const byte BACKWARD = 1;
  static const byte LEFT = 2;
  static const byte LEFT_TURN = 2;
  static const byte RIGHT = 3;
  static const byte RIGHT_TURN = 3;
  static const byte REDLED = 4;
  static const byte WHITELED = 5;
  static const byte BUZZER = 6;
  static const byte FREE = 7;
  
  //Fixed pins
  static const byte speed_left = 9;//conflit avec Servo.h
  static const byte speed_right = 10;//conflit avec Servo.h
  
  static const byte mot_left = 11;
  static const byte mot_right = 12;
  static const byte servo1 = 6;
  static const byte servo2 = 5;
  
  static const byte moustache_left = 2;
  static const byte moustache_right = 3;
  
  static const byte led_red = 7;
  static const byte led_white = 8;
  
  static const byte buzzer = 13;
  static const byte free = 4;
  
  static const byte ldr_left = A0;
  static const byte ldr_right = A1;
  
  
  TSRobuno():mServoMode(false)
  {
    enableMotor();
  }
  
  void enableServo()
  {
    mServoMode = true;
    s1.attach(servo1);
    s2.attach(servo2);
  }
  
  //Impossible de désactiver
  /*void disableServo()
  {
    mServoMode = false;
    s1.write(0, true);
    s2.write(0, true);
    s1.detach();
    s2.detach();
    enableMotor();
  }*/
  
  void enableMotor()
  {
    pinMode(mot_left, OUTPUT);
    pinMode(mot_right, OUTPUT);
    pinMode(speed_left, OUTPUT);
    pinMode(speed_right, OUTPUT);
  }
  
  void run(byte direction, byte speed)
  {
    if(!mServoMode)
    {
      switch(direction)
      {
        case RIGHT:
          digitalWrite(mot_left, HIGH);
          digitalWrite(mot_right, LOW);
        break;
        case LEFT:
          digitalWrite(mot_left, LOW);
          digitalWrite(mot_right, HIGH);
        break;
        case FRONT:
          digitalWrite(mot_left, HIGH);
          digitalWrite(mot_right, HIGH);
        break;
        case BACK:
          digitalWrite(mot_left, LOW);
          digitalWrite(mot_right, LOW);
        break;
      }
      int finalSpeed = map(speed, 0, 255, 0, 1023);
      analogWrite(speed_left, finalSpeed);
      analogWrite(speed_right, finalSpeed);
    }
    else
    {
      switch(direction)
      {
        case RIGHT:
          servoWrite(s1, speed, true);
          servoWrite(s2, speed, true);
        break;
        case LEFT:
          servoWrite(s1, speed, false);
          servoWrite(s2, speed, false);
        break;
        case FRONT:
          servoWrite(s1, speed, false);
          servoWrite(s2, speed, true);
        break;
        case BACK:
          servoWrite(s1, speed, true);
          servoWrite(s2, speed, false);
        break;
      }
    }
  }
  
  //From TSServo
  static void servoWrite(Servo& s, byte value, bool inverse)
  {
    int val = map(value, 0, 255, 0, 90);
    float angle = (float)val * ((float) value / 255);
    int temp = 90+(inverse?-angle:angle);
    s.write(temp);
  }
      
  void stop()
  {
    if(!mServoMode)
    {
      analogWrite(speed_left, 0);
      analogWrite(speed_right, 0);
    }
    else
    {
      servoWrite(s1, 0, false);
      servoWrite(s2, 0, false);
    }
  }
  
  byte read(byte moustacheID)
  {
    if(moustacheID == LEFT) moustacheID = moustache_left;
    else if(moustacheID == RIGHT) moustacheID = moustache_right;
    else moustacheID = free;
    pinMode(moustacheID, INPUT);
    return digitalRead(moustacheID);
  }
  
  void write(byte outputID, byte status)
  {
    if(outputID == REDLED) outputID = led_red;
    else if(outputID == WHITELED) outputID = led_white;
    else if(outputID == BUZZER) outputID = buzzer;
    else if(outputID == FREE) outputID = free;
    pinMode(outputID, OUTPUT);
    digitalWrite(outputID, status);
  }
  
  int ldr_read(byte ldrID)
  {
    if(ldrID == LEFT) ldrID = ldr_left;
    else if(ldrID == RIGHT) ldrID = ldr_right;
    pinMode(ldrID, INPUT);
    return analogRead(ldrID); 
  }
  
  public:
  bool mServoMode;
  Servo s1, s2;
  
};

#endif
