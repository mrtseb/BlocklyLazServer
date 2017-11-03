#include "TSTools.h"

String parseString(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void updateComVariable(String com, String prefix, int &var)
{
  String label = parseString(com,':', 0);
  if(label == prefix)
  {
    var = parseString(com, ':', 1).toInt();
  }
}
float getDistance(byte pin)
{
  int sensor_value;
  int sum;
  pinMode(pin, INPUT);
  // read the analog in value:
  for (int i = 0;i < 20;i ++)//Continuous sampling 20 times
  {
    sensor_value = analogRead(pin); 
    sum += sensor_value;
  }
  sensor_value = sum / 20;

  return  200.3775040589502
            - 2.2657665648980 * sensor_value
            + 0.0116395328796 * sensor_value* sensor_value
            - 0.0000299194195 * sensor_value* sensor_value* sensor_value
            + 0.0000000374087 * sensor_value* sensor_value* sensor_value* sensor_value
            - 0.0000000000181 * sensor_value* sensor_value* sensor_value* sensor_value* sensor_value;
} 
