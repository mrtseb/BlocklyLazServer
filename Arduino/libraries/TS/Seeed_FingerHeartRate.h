
#ifndef FINGERHEARTRATE_H
#define FINGERHEARTRATE_H

#include "Arduino.h"
#include "virtualGroveConnector.h"


class Seeed_FingerHeartRate : public virtualGroveConnector
{
    private:
        int fr;
		
    public:
	    Seeed_FingerHeartRate() : virtualGroveConnector() {};
	    ~Seeed_FingerHeartRate() {};

        bool isAvailable() {
			Wire.requestFrom(0xA0 >> 1, 1);    // request 1 bytes from slave device
			fr = 0;
			if (Wire.available())  // slave may send less than requested
			{         
				fr = (int) Wire.read();   // receive heart rate value (a byte)
				return true;
			}
			return false;
		}
       
		int read() {
			return fr;
		}

};

#endif //FINGERHEARTRATE_H
