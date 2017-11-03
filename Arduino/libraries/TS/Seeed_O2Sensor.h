/*    
 * Seeed_O2Sensor.h
 * 
 */
 
#ifndef Seeed_O2SENSOR_H
#define Seeed_O2SENSOR_H

#include "Arduino.h"

const float VReferO2Sensor = 3.3;       // voltage of adc reference

class Seeed_O2Sensor 
{
    private:
	    boolean _isAvailable;
		  int AX0Pin;
        
    public:
      Seeed_O2Sensor(int AX0Pin);
      Seeed_O2Sensor(int AX0Pin, int AX1Pin);
	    ~Seeed_O2Sensor();
		
	    int readSensor();
	    int getConcentration() ;
		

};

#endif //__Seeed_GASSENSOR_H__
