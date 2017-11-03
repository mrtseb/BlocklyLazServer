/*    
 * Seeed_GasSensor.h
 * 
 */
 
#ifndef Seeed_GASSENSOR_H
#define Seeed_GASSENSOR_H

#include <SoftwareSerial.h>
#include "Arduino.h"
#include "virtualGroveConnector.h"

const unsigned char cmd_get_sensor[] =
{
    0xff, 0x01, 0x86, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x79
};
const unsigned char cmd_calibrate[] = 
{
    0xff, 0x87, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf2
};
class Seeed_GasSensor : public virtualGroveConnector, SoftwareSerial
{
    private:
	    //SoftwareSerial *sensor; // software serial
	    boolean _isAvailable;
	    boolean checkBitValidationUART(byte *raw);
		
		unsigned char dataRevice[9];
		int _CO2PPM;
		int _temperature;
        
    public:
	    Seeed_GasSensor(int RXPin, int TXPin);
	    ~Seeed_GasSensor();

		bool calibrateSensor();
		bool readSensor();
	    boolean sensorIsAvailable();
	    int getTemperature() { return _temperature; };
	    int getCO2PPM() { return _CO2PPM; };
		
		//--  
		int litValeur(String valeurType)
		{
			if ((valeurType=="Temperature") || (valeurType=="T"))
			{
				return getTemperature();      
			} else if ((valeurType=="CO2") || (valeurType=="C"))
			{				
				return getCO2PPM();      
			} else {			
				return 0;
			}
		}
		
		// mblock
		int litValeur(unsigned char firstchar)
		{
			if (firstchar=='T')
			{
				return getTemperature();      
			} else if (firstchar=='C')
			{				
				return getCO2PPM();      
			} else {			
				return 0;
			}
		}
};

#endif //__Seeed_GASSENSOR_H__
