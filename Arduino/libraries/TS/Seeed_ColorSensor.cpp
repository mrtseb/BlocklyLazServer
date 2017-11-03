#include "Seeed_ColorSensor.h"
#include <Wire.h>
#include <math.h>

// Default constructor
Seeed_ColorSensor::Seeed_ColorSensor()
	: virtualGroveConnector(), triggerMode_(INTEG_MODE_FREE | INTEG_PARAM_PULSE_COUNT1)
	, interruptSource_(INT_SOURCE_CLEAR)
	, interruptMode_(INTR_LEVEL | INTR_PERSIST_EVERY)
	, gainAndPrescaler_(GAIN_1 | PRESCALER_1)
	, sensorAddress_(COLOR_SENSOR_ADDR)
{	
	// move code to init fonction
	/*
	Seeed_ColorSensor::setTimingReg(); 
	Seeed_ColorSensor::setInterruptSourceReg();  
	Seeed_ColorSensor::setInterruptControlReg(); 
	Seeed_ColorSensor::setGain(); 
	Seeed_ColorSensor::setEnableADC(); 
	*/
}

// Constructor with parameters
Seeed_ColorSensor::Seeed_ColorSensor(
	  const int& triggerMode
	, const int& interruptSource
	, const int& interruptMode
	, const int& gainAndPrescaler
	, const int& sensorAddress)
	: virtualGroveConnector(), triggerMode_(triggerMode)
	, interruptSource_(interruptSource)
	, interruptMode_(interruptMode)
	, gainAndPrescaler_(gainAndPrescaler)
	, sensorAddress_(sensorAddress) 
{}


void Seeed_ColorSensor::init(int ledstatus)
{
   Wire.begin();
   Seeed_ColorSensor::setTimingReg(); 
   Seeed_ColorSensor::setInterruptSourceReg();  
   Seeed_ColorSensor::setInterruptControlReg(); 
   Seeed_ColorSensor::setGain(); 
   Seeed_ColorSensor::setEnableADC(); 
   ledStatus = ledstatus;  
}

void Seeed_ColorSensor::setTimingReg()
{
	Wire.beginTransmission(sensorAddress_);
	Wire.write(REG_TIMING);
	Wire.write(triggerMode_);
	Wire.endTransmission();  
	delay(10); 
}

void Seeed_ColorSensor::setInterruptSourceReg()
{
	Wire.beginTransmission(sensorAddress_);
	Wire.write(REG_INT_SOURCE);
	Wire.write(interruptSource_);
	Wire.endTransmission();  
	delay(10);
}

void Seeed_ColorSensor::setInterruptControlReg()
{
	Wire.beginTransmission(sensorAddress_);
	Wire.write(REG_INT);
	Wire.write(interruptMode_);
	Wire.endTransmission();  
	delay(10);
}

void Seeed_ColorSensor::setGain()
{
	Wire.beginTransmission(sensorAddress_);
	Wire.write(REG_GAIN);
	Wire.write(gainAndPrescaler_);
	Wire.endTransmission();
}

void Seeed_ColorSensor::setEnableADC()
{
	Wire.beginTransmission(sensorAddress_);
	Wire.write(REG_CTL);
	Wire.write(CTL_DAT_INIITIATE);
	Wire.endTransmission();  
	delay(10);  
}

void Seeed_ColorSensor::clearInterrupt()
{
	Wire.beginTransmission(sensorAddress_);
	Wire.write(CLR_INT);
	Wire.endTransmission(); 
}

void Seeed_ColorSensor::readRGB()
{
	Wire.beginTransmission(sensorAddress_);
	Wire.write(REG_BLOCK_READ);
	Wire.endTransmission();
	
	Wire.beginTransmission(sensorAddress_);
	Wire.requestFrom(sensorAddress_, 8);
	delay(100);
	
	// if two bytes were received
	if(8 <= Wire.available())
	{
		int i;
		for(i = 0; i < 8; ++i)
		{
			readingdata_[i] = Wire.read();
			//Serial.println(readingdata_[i], BIN);
		}
	}
	green_	= readingdata_[1] * 256 + readingdata_[0];
	red_ 	= readingdata_[3] * 256 + readingdata_[2];
	blue_	= readingdata_[5] * 256 + readingdata_[4];
	clear_	= readingdata_[7] * 256 + readingdata_[6];
	
	/*Serial.print("The RGB value are: RGB( ");
	Serial.print(red_,DEC);
	Serial.print(", ");
	Serial.print(green_,DEC);
	Serial.print(", ");
	Serial.print(blue_,DEC);
	Serial.println(" )");
	Serial.print("The Clear channel value are: ");
	Serial.println(clear_,DEC);*/
}

int Seeed_ColorSensor::litCouleur(String couleur)
{
    readRGB(&red,&green,&blue);
    if (couleur=="Bleu")
    {
        return blue;      
    } else if (couleur=="Vert")
    {
        return green;      
    } else {
        return red; 
    }
}

int Seeed_ColorSensor::litCouleur(char couleur)
{
    readRGB(&red,&green,&blue);
    if (couleur=='B')
    {
        return blue;      
    } else if (couleur=='V')
    {
        return green;      
    } else { //'R'
        return red; 
    }
}

void Seeed_ColorSensor::readRGB(int *red, int *green, int *blue)
{
	Wire.beginTransmission(sensorAddress_);
	Wire.write(REG_BLOCK_READ);
	Wire.endTransmission();
	
	Wire.beginTransmission(sensorAddress_);
	Wire.requestFrom(sensorAddress_, 8);
	delay(100);

	// if two bytes were received
	if(8 <= Wire.available())
	{
		int i;
		for(i = 0; i < 8; ++i)
		{
			readingdata_[i] = Wire.read();
			//Serial.println(readingdata_[i], BIN);
		}
	}
	green_	= readingdata_[1] * 256 + readingdata_[0];
	red_ 	= readingdata_[3] * 256 + readingdata_[2];
	blue_	= readingdata_[5] * 256 + readingdata_[4];
	clear_	= readingdata_[7] * 256 + readingdata_[6];
	
	double tmp;
	int maxColor;
	
	if ( ledStatus == 1 )
	{
		red_  = red_  * 1.70;
		blue_ = blue_ * 1.35;

		maxColor = max(red_, green_);
		maxColor = max(maxColor, blue_);
	   
		if(maxColor > 255)
		{
			tmp = 250.0/maxColor;
			green_	*= tmp;
			red_ 	*= tmp;
			blue_	*= tmp;
		}
	}
	if ( ledStatus == 0 )
	{
		maxColor = max(red_, green_);
		maxColor = max(maxColor, blue_);
	   
		tmp = 250.0/maxColor;
		green_	*= tmp;
		red_ 	*= tmp;
		blue_	*= tmp;

	}
	
	int minColor = min(red_, green_);
	minColor = min(maxColor, blue_);
	maxColor = max(red_, green_);
	maxColor = max(maxColor, blue_);
	
	int greenTmp = green_;
	int redTmp 	 = red_;
	int blueTmp	 = blue_;
	
//when turn on LED, need to adjust the RGB data,otherwise it is almost the white color
	if(red_ < 0.8*maxColor && red_ >= 0.6*maxColor)
	{
		red_ *= 0.4;
    }
	else if(red_ < 0.6*maxColor)
	{
		red_ *= 0.2;
    }
	
	if(green_ < 0.8*maxColor && green_ >= 0.6*maxColor)
	{
		green_ *= 0.4;
    }
	else if(green_ < 0.6*maxColor)
	{
		if (maxColor == redTmp && greenTmp >= 2*blueTmp && greenTmp >= 0.2*redTmp)				//orange
		{
			green_ *= 5;
		}
		green_ *= 0.2;
    }
	
	if(blue_ < 0.8*maxColor && blue_ >= 0.6*maxColor)
	{
		blue_ *= 0.4;
    }
	else if(blue_ < 0.6*maxColor)
	{
		if (maxColor == redTmp && greenTmp >= 2*blueTmp && greenTmp >= 0.2*redTmp)				//orange
		{
			blue_ *= 0.5;
		}
		if (maxColor == redTmp && greenTmp <= blueTmp && blueTmp >= 0.2*redTmp)					//pink
		{
			blue_  *= 5;
		}
		blue_ *= 0.2;
    }
	
	minColor = min(red_, green_);
	minColor = min(maxColor, blue_);
	if(maxColor == green_ && red_ >= 0.85*maxColor && minColor == blue_)						//yellow
	{
		red_ = maxColor;
		blue_ *= 0.4;
    }
	
	*red   = red_;
	*green = green_;
	*blue  = blue_;
}

void Seeed_ColorSensor::calculateCoordinate()
{
	double X;
	double Y;
	double Z;
	double x;
	double y;
	
	X = (-0.14282) * red_ + (1.54924) * green_ + (-0.95641) * blue_;
	Y = (-0.32466) * red_ + (1.57837) * green_ + (-0.73191) * blue_;
	Z = (-0.68202) * red_ + (0.77073) * green_ + (0.563320) * blue_;
	
	x = X / (X + Y + Z);
	y = Y / (X + Y + Z);
	
	if( (X > 0) && ( Y > 0) && ( Z > 0) )
	{
		Serial.println("The x,y values are(");
		Serial.print(x, 2);
		Serial.print(" , ");
		Serial.print(y, 2);
		Serial.println(")");
	}
	else
		Serial.println("Error: overflow!");
}
