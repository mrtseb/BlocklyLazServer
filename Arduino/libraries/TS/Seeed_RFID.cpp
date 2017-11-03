/*    
 * SeeedRFID.cpp
 * A library for RFID moudle.
 *   
 * Copyright (c) 2008-2014 seeed technology inc.  
 * Author      : Ye Xiaobo(yexiaobo@seeedstudio.com)
 * Create Time: 2014/2/20
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**************************************************************************
* Pins
* ====
*
* 1. VCC support 3.3 ~ 5V
* 2. TX, RX connect to Arduino or Seeeduino
* 3. T1, T2 is the Signal port for RFID antenna
* 4. W0, W1 is for wiegand protocol, but this library not support yet.
* 
* ```
* 		+-----------+
* 	----|VCC	  T1|----
* 	----|GND	  T2|----
* 	----|TX		 SER|----
* 	----|RX		 LED|----	
* 	----|W0		BEEP|----
* 	----|W1		 GND|----
* 		+-----------+
* ```
***************************************************************************/

#include <SoftwareSerial.h>
#include "Seeed_RFID.h"
#include "Arduino.h"

Seeed_RFID::Seeed_RFID(int rxPin, int txPin) : virtualGroveConnector ()
{
     _rfidIO = new SoftwareSerial(rxPin, txPin);
     _rfidIO->begin(9600);
     _rfidIO->setTimeout(50);
  
  	// init RFID data
  	_data.dataLen = 0;
  	_data.chk = 0;
  	_data.valid = false;
  
  	_isAvailable = false;
  	_type = RFID_UART;
}

Seeed_RFID::~Seeed_RFID()
{
}


boolean Seeed_RFID::checkBitValidationUART(char *raw)
{
    byte check[14];
    for (int iRaw= 1; iRaw<13; iRaw++)
    { 
        if (_data.raw[iRaw]<58)   //0-9
        {
            check[iRaw] = raw[iRaw]-48;
        } else if (raw[iRaw]<71) //A-F
        {
            check[iRaw] = 10+raw[iRaw]-65;
        }
    }
  	if ((check[11]   ==  (check[1] ^ check[3] ^ check[5] ^ check[7] ^ check[9]))  &&
        (check[12]   ==  (check[2] ^ check[4] ^ check[6] ^ check[8] ^ check[10])) )
  	{
  		  _data.valid = _isAvailable = true;
  		  return true;
  	} else
  	{
  		  _data.valid = _isAvailable = false;
  		  return false;
  	}
}

boolean Seeed_RFID::read()
{

	_isAvailable = false;

	if (_data.dataLen != 0)
	{
		_data.dataLen = 0;
	}

	while (_rfidIO->available())
	{
		_data.raw[_data.dataLen++] = _rfidIO->read();
		delay(10);
	}

  if ((_data.dataLen>13) && (checkBitValidationUART(_data.raw)))
  {
      _data.raw[11] = '\0';
      String val    = String(&(_data.raw[5]));
      _data.value   = strtol(&(_data.raw[5]), NULL, 16);
  }  

	return _isAvailable; 
}

static long hex2dec(String hexCode)
{
    char buf[19] = "";
    hexCode.toCharArray(buf, 18);
    return strtol(buf, NULL, 16);
}
  
boolean Seeed_RFID::read0()
{

    _isAvailable = false;
    unsigned long time0;
    if (_rfidIO->available())
    {
      time0 = millis();
    }
    String raw = _rfidIO->readString();
    
    if(raw.length()>=14)
    {
        //Checksum check
        _data.raw[0] = hex2dec(raw.substring(1,3));
        _data.raw[1] = hex2dec(raw.substring(3,5));
        _data.raw[2] = hex2dec(raw.substring(5,7));
        _data.raw[3] = hex2dec(raw.substring(7,9));
        _data.raw[4] = hex2dec(raw.substring(9,11));
        _data.raw[5] = hex2dec(raw.substring(11,13));
  
        if((_data.raw[0] ^ _data.raw[1] ^ _data.raw[2] ^ _data.raw[3] ^ _data.raw[4]) == _data.raw[5])
        {
            Serial.println(String(hex2dec(raw.substring(3,11))));
        }
    }
    return 1; 
}



boolean Seeed_RFID::isAvailable()
{
  	switch(_type)
  	{
  		case RFID_UART:
  			return Seeed_RFID::read();
  			break;
  		case RFID_WIEGAND:
  			return false;
  			break;
  		default:
  			return false;
  			break;
  	}
}

RFIDdata Seeed_RFID::data()
{
  	if (_data.valid)
  	{
  		return _data;
  	}else{
  		// empty data
  		RFIDdata _tag;
  		return _tag;
  	}
}

unsigned long Seeed_RFID::cardNumber()
{
  return _data.value;
  
  	/*// unsigned long myZero = 255;
  
  	unsigned long sum = 0;
  	if(0 != _data.raw[0]){
  		// _data.raw[0] = 	_data.raw[0] & myZero;
  		sum = sum + _data.raw[0];
  		sum = sum<<24;
  	}
  	// _data.raw[1] = 	_data.raw[1] & myZero;
  	sum = sum + _data.raw[1];
  	sum = sum<<16;
  
  	unsigned long sum2 = 0;
  	// _data.raw[2] = 	_data.raw[2] & myZero;
  	sum2 = sum2  + _data.raw[2];
  	sum2 = sum2 <<8;
  	// _data.raw[3] = 	_data.raw[3] & myZero;
  	sum2 = sum2  + _data.raw[3];
  
  	sum = sum + sum2;
  
  #ifdef DEBUG
  	Serial.print("cardNumber(HEX): ");
      Serial.println(sum, HEX);
  	Serial.print("cardNumber: ");
      Serial.println(sum);
  #endif
  
      return sum;
*/
}
