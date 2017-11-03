/*
*Library Technologie Services
* Copyright © 2016 by Technologie Services. All rights reserved
Version 1
<http://www.technologieservices.fr>
*/

#ifndef TSDigitalTube_H
#define TSDigitalTube_H

#include "TM1637.h"

class TSDigitalTube: public TM1637
{
  public:
  TSDigitalTube():TM1637(), mPort(0), mDots(0){;}//empty ctor
  void init(byte port)//two step ctor
  {
    TM1637::begin(port, port+1);//CLK, DIO
    TM1637::setBrightness(0x0f);
    mPort=port;
  }
  void show(byte port, short value)
  {
    if(port != mPort) init(port);
    TM1637::showNumberDec(value, false, 4, 0, mDots);
  }
  void showDots(bool show)
  {
    mDots = show;
  }
  //Online version
  void show(byte port, byte val1, byte val2, bool dots)
  {
    short value = constrain(val1, 0, 99) * 100;
    value+=constrain(val2, 0, 99);
    if(port != mPort) init(port);
    TM1637::showNumberDec(value, true, 4, 0, dots);
  }
  //Online version
  void show(byte port, int value, bool dots)
  {
    if(port != mPort) init(port);
    TM1637::showNumberDec(value, true, 4, 0, dots);
  }
  private:
  byte mPort;
  bool mDots;
};
 
#endif
