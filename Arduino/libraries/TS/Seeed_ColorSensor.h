/****************************************************************************/	
//	Hardware: Grove - I2C Color Sensor
//  Arduino IDE: Arduino-1.6
//  
//  Refactored version of the library by FrankieChu - www.seeedstudio.com
//	
/******************************************************************************/

#ifndef SEEED_COLORSENSOR
#define SEEED_COLORSENSOR

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Registers.h"
#include "virtualGroveConnector.h"

class Seeed_ColorSensor : public virtualGroveConnector
{
public:

	// Color Sensor LED Status
	int ledStatus;
	// Default constructor
	Seeed_ColorSensor();
	// Constructor with parameters
	Seeed_ColorSensor(
		  const int& triggerMode
		, const int& interruptSource
		, const int& interruptMode
		, const int& gainAndPrescaler
		, const int& sensorAddress);

    void init(int ledstatus);
	void readRGB();
	void readRGB(int *red, int *green, int *blue);
	void calculateCoordinate();
	void clearInterrupt();

	int litRouge () { readRGB(&red,&green,&blue);  return red;}
	int litVert ()  { readRGB(&red,&green,&blue);  return green;}
	int litBleu ()  { readRGB(&red,&green,&blue);  return blue;}
	int litCouleur (String couleur);
	int litCouleur (char couleur);
	
private:	 
	int red, green, blue; 
	// Set trigger mode. Including free mode, manually mode, single synchronization mode or so.
	void setTimingReg();
	// Set interrupt source
	void setInterruptSourceReg();
	// Set interrupt mode
	void setInterruptControlReg();
	// Set gain value and pre-scaler value
	void setGain();
	// Start ADC of the colour sensor
	void setEnableADC();
	
	// Used for storing the colour data
	int readingdata_[8];
	int green_;
	int red_;
	int blue_;
	int clear_;
	
	int triggerMode_;	
	int interruptSource_;
	int interruptMode_;
	int gainAndPrescaler_;
	int sensorAddress_;
	
};

#endif
