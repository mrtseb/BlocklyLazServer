/*
*Library Technologie Services
* Copyright © 2016 by Technologie Services. All rights reserved
Version 1
<http://www.technologieservices.fr>
*/

#ifndef TSLedBarOnline_H
#define TSLedBarOnline_H

#include "Grove_LED_Bar.h"

class TSLedBar
{
	public:
	TSLedBar(){;}
  void init(byte pin)
  {
    if(mLedBar) delete mLedBar;
    mLedBar = new Grove_LED_Bar(pin + 1, pin , true);
  }
	void setLevel(int pin, byte value)
	{
    if(!mLedBar) init(pin);
		mLedBar->setLevel((float)value/10);
	}
  private:
    Grove_LED_Bar *mLedBar;
};

#endif
