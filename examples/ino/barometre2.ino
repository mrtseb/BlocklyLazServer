#include <Servo.h>

int pression;
int angle;

Servo myServo5;

void setup() {
  Serial.begin(9600);
  myServo5.attach(5);
}

void loop() {
  pression = (int)(770);
  angle = (int)((790 - pression / 133.3224) * 3);
  myServo5.write(angle);
  Serial.println((String("P:") + String(pression) + String(" Pa.") + String(" angle:") + String(angle)));

}
