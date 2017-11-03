/*    
 * Seeed_O2Sensor.cpp
 * 
 */
 
#include "Seeed_O2Sensor.h"

Seeed_O2Sensor::Seeed_O2Sensor(int AX0Pin) 
{
	  AX0Pin = AX0Pin;
}

Seeed_O2Sensor::Seeed_O2Sensor(int AX0Pin, int AX1Pin) 
{
    AX0Pin = AX0Pin;
}

Seeed_O2Sensor::~Seeed_O2Sensor()
{
}

int Seeed_O2Sensor::readSensor()
{
    long sum = 0;
    for(int i=0; i<32; i++)
    {
        sum += analogRead(AX0Pin);
    }

    sum >>= 5;

    float MeasuredVout = sum * (VReferO2Sensor / 1023.0);
    return MeasuredVout;
}


int Seeed_O2Sensor::getConcentration()
{
    // Vout samples are with reference to 3.3V
    float MeasuredVout = readSensor();

    //float Concentration = FmultiMap(MeasuredVout, VoutArray,O2ConArray, 6);
    //when its output voltage is 2.0V,
    float Concentration = MeasuredVout * 0.21 / 2.0;
    float Concentration_Percentage=Concentration*100;
    return Concentration_Percentage;
}
