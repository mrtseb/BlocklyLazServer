/*    
 * Seeed_GasSensor.h
 * 
 */
 
#ifndef Seeed_DUSTSENSOR_H
#define Seeed_DUSTSENSOR_H

#include "Arduino.h"
#include "virtualGroveConnector.h"

class Seeed_DustSensor : public virtualGroveConnector
{
    unsigned long duration;
    unsigned long starttime;
    unsigned long sampletime_ms ;//sampe 30s ;
    unsigned long lowpulseoccupancy ;
    float ratio ;
    float concentration ;   
       
    public:
      Seeed_DustSensor(int RXPin, int sampleTime);
      ~Seeed_DustSensor();

      void setup();
      float readConcentration();
      bool isValid() { return _isValid; };

    private :
      int currPin;
      bool _isValid;
  
};

#endif //Seeed_DUSTSENSOR_H

