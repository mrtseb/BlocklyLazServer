/*
*Library Technologie Services
* Copyright � 2016 by Technologie Services. All rights reserved
Version 1
<http://www.technologieservices.fr>
*/

#ifndef TSServo_H
#define TSServo_H

#include <Servo.h>

class TSServo : public Servo
{
	public:
	TSServo():Servo(){mTrim=0;mPin=0;}
  void init(int pin)
  {
    mPin=pin;
    Servo::attach(mPin);
  }
  /*  value: 0-255 for mBlock use
  */
  void write(int pin, int value, int speed)
	{
    if(pin!=mPin)
    {
      init(pin);
    }
		int finalValue = map(constrain(value, 0, 255), 0, 255, 544, 2400);
		int currentValue = Servo::readMicroseconds();
		int	delta	= finalValue - currentValue;
    float increment = (float)speed/1000;
    //Synchronous move
		if(delta>0)
    {
			for(float i=0; i<=delta;i+=increment)
      {
					Servo::writeMicroseconds(currentValue+i);
			}
    }
    else
    {
			for(float i=0; i>=delta;i-=increment)
      {
					Servo::writeMicroseconds(currentValue+i);
			}
		}
    Servo::writeMicroseconds(finalValue);
  }
  
  /*  value: 0-255 for mBlock use
  */
  void write(int pin, int value, bool inverse, int trim)
	{
		setTrim(trim);
    if(pin!=mPin)
    {
      init(pin);
    }
    value = constrain(value, 0, 255);
		int val = map(value, 0, 255, 0, 90);
    mAngle = (float)val * ((float) value / 255);
    float temp = 90.0f+(inverse?-mAngle:mAngle)+mTrim;
    Servo::write(temp);
  }
  
  void setTrim(short trim)
  {
    mTrim=trim;
  }
  
  private:
  short mTrim;
  float mAngle;
  int   mPin;
};

#endif
