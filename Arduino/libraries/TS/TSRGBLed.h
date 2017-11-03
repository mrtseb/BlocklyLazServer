/*
*Library Technologie Services
* Copyright © 2016 by Technologie Services. All rights reserved
Version 1
<http://www.technologieservices.fr>
*/

#ifndef TSRGBLed_H
#define TSRGBLed_H

#include "ChainableLED.h"

class TSRGBLed
{
  public:
  TSRGBLed():mLed(0),mClkPin(0){;}//empty ctor
  void init(byte clk_pin, byte data_pin)//two step ctor
  {
    if(mLed) delete mLed;
    mLed = new ChainableLED(clk_pin, data_pin, 10);
    mClkPin=clk_pin;
    mLed->init();
  }
  void setColorRGB(byte clk_pin, byte data_pin, byte led, byte red, byte green, byte blue)
  {
    if(!mLed || clk_pin != mClkPin)
    {
      init(clk_pin, data_pin);
    }
    mLed->setColorRGB(led, red, green, blue);
  }
  private:
  ChainableLED *mLed;
  byte mClkPin;
};
 
#endif
