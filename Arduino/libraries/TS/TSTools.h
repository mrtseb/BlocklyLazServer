#ifndef TSTools_H
#define TSTools_H

#include <Arduino.h>

String parseString(String data, char separator, int index);
float getDistance(byte pin);
void updateComVariable(String com, String prefix, int &var);

#endif
