/*
*Library Technologie Services
* Copyright © 2016 by Technologie Services. All rights reserved
Version 1
<http://www.technologieservices.fr>
*/

#ifndef TSJoystick_H
#define TSJoystick_H

float getJoystick(int mode, int pin)
{
  if(mode == 0)
  {
    return analogRead(pin);
  }
  else if(mode == 1)
  {
    return analogRead(pin+1);
  }
  else
  {
    return analogRead(pin) > 1000;
  }
}
 
#endif
