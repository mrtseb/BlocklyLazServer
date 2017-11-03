/*    
 * Seeed_GasSensor.cpp
 * 
 */
 
#include "Seeed_GasSensor.h"

Seeed_GasSensor::Seeed_GasSensor(int RXPin, int TXPin)  : virtualGroveConnector(), SoftwareSerial(RXPin, TXPin)
{
    /// SoftwareSerial init
    begin(9600);
    setTimeout(50);

    //gassensor init
  	_isAvailable = false;
	  _temperature = 0;
	  _CO2PPM 		= 0;
}

Seeed_GasSensor::~Seeed_GasSensor()
{
}

boolean Seeed_GasSensor::checkBitValidationUART(byte *data)
{
	return ((1 + (0xFF ^ (byte)(data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7]))) == data[8]);
}

bool Seeed_GasSensor::calibrateSensor()
{
	for(int i=0; i<sizeof(cmd_calibrate); i++)
    {
        write(cmd_calibrate[i]);
    }
	return true;
}

bool Seeed_GasSensor::readSensor()
{
	  _isAvailable = false;

    byte data[9];
    int i = 0;

    //transmit command data to softwareserial
    for(i=0; i<sizeof(cmd_get_sensor); i++)
    {
        write(cmd_get_sensor[i]);
    }
    delay(10);
    // begin reveiceing data from softwareserial
    if (available())
    {
        while (available())
        {
            for(int i=0;i<9; i++)
            {
                data[i] = read();
            }
        }
    }
	
    if((i == 9) && (checkBitValidationUART(data)))
    {
      _isAvailable = true;
		  _CO2PPM 		= (int)data[2] * 256 + (int)data[3];
		  _temperature = (int)data[4] - 40;
	  }

	  return _isAvailable; 
}



boolean Seeed_GasSensor::sensorIsAvailable()
{
	  return _isAvailable; 
}
