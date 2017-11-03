/*
*Library Technologie Services
* Copyright © 2016 by Technologie Services. All rights reserved
Version 1
<http://www.technologieservices.fr>
*/

#ifndef TSTemperature_H
#define TSTemperature_H

#include <math.h>

/*
value = voltage
R = Zero power resistance
B = B constant
*/
float getTemperature(int value, const float R, const int B)
{
  float resistance=(float)(1023-value)*R/value;
  float temperature=1.0f/(log(resistance/R)/B+1/298.15)-273.15;
  return temperature;
}

/*
Sec: 0 - 300      -> retourne 0
Humide: 300 - 700 -> retourne 1
Eau: 700 - 950    -> retourne 2
*/
int getHumidity(byte pin)
{
  int rawValue = analogRead(pin);
  if(rawValue>700)
  {
    return 2;
  }
  else if(rawValue>300)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

#endif
