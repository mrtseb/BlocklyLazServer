#ifndef TSi2cMotorDriver_H
#define TSi2cMotorDriver_H

//From: https://github.com/Seeed-Studio/Grove_I2C_Motor_Driver/blob/master/I2CMotorDriverDemoCode/I2CMotorDriverDemoCode.ino

#include <Wire.h>

#define MotorSpeedSet 		0x82
#define DirectionSet        0xaa
#define Nothing             0x01
#define I2CMotorDriverAdd 	0x0f

class TSi2cMotorDriver
{
	public:
	TSi2cMotorDriver(){;}
	enum Directions
	{
		FORWARD=0b0110,
		BACKWARD=0b1001,
		LEFT=0b0100,
		RIGHT=0b0010,
		LEFT_TURN=0b0101,
		RIGHT_TURN=0b1010,
		STOP=0b0000
	};
	void begin(){Wire.begin();delay(10);}
	void MotorSpeedSetAB(byte MotorSpeedA , byte MotorSpeedB)
	{
		MotorSpeedA=constrain(MotorSpeedA,0,255);
		MotorSpeedB=constrain(MotorSpeedB,0,255);
		Wire.beginTransmission(I2CMotorDriverAdd); 	// transmit to device I2CMotorDriverAdd
		Wire.write(MotorSpeedSet);        			// set pwm header
		Wire.write(MotorSpeedA);             		// send pwma
		Wire.write(MotorSpeedB);              		// send pwmb
		Wire.endTransmission();    					// stop transmitting
		delay(4);
	}
	//set the direction of DC motor. 
	void MotorDirectionSet(byte Direction)
	{
		//  Adjust the direction of the motors 0b0000 I4 I3 I2 I1
		Wire.beginTransmission(I2CMotorDriverAdd); 	// transmit to device I2CMotorDriverAdd
		Wire.write(DirectionSet);        			// Direction control header
		Wire.write(Direction);              		// send direction control information
		Wire.write(Nothing);              			// need to send this byte as the third byte(no meaning)
		Wire.endTransmission();    					// stop transmitting
	}
};

#endif
