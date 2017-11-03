#include "Seeed_DustSensor.h"

Seeed_DustSensor::Seeed_DustSensor(int RXPin, int sampleTime) : virtualGroveConnector()
{
    sampletime_ms     = sampleTime;//sampe 30s ;
    lowpulseoccupancy = 0;
    ratio             = 0;
    concentration     = 0; 
    _isValid          = false;
      
    currPin = RXPin;
}

Seeed_DustSensor::~Seeed_DustSensor()
{
}

void Seeed_DustSensor::setup() 
{    
    pinMode(currPin,INPUT);
    starttime = millis();//get the current time;
  
}

float Seeed_DustSensor::readConcentration() 
{
    duration = pulseIn(currPin, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;

    if ((millis()-starttime) > sampletime_ms)//if the sampel time == 10s
    {
        ratio             = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
        concentration     = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
        lowpulseoccupancy = 0;

        _isValid = true;
        starttime = millis();
    }
    return concentration;
}

   
