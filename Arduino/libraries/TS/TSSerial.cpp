/*
*Library Technologie Services
* Copyright © 2016 by Technologie Services. All rights reserved
Version 1
<http://www.technologieservices.fr>
*/

#include "TSSerial.h"
#include "TSTools.h"
  
TSSerial::TSSerial():mSerial(0),mTx(0), mRx(0)
{
}

void TSSerial::init(byte rx, byte tx, unsigned long speed=115200)
{
  if(mSerial) delete mSerial;
  mRx = rx;
  mTx = tx;
  mSerial = new SoftwareSerial(mRx, mTx);
  mSerial->begin(speed);
  mSerial->setTimeout(100);
}

void TSSerial::send(byte rx, byte tx, String data)
{
  if(!mSerial) init(rx, tx);
  mSerial->print(data);
}

void TSSerial::send(byte rx, String data)
{
  send(rx, rx+1, data);
}

String TSSerial::receive(byte rx, byte tx)
{
  if(!mSerial) init(rx, tx);
  if(mSerial->available())
  {
    return mSerial->readString();
  }
  return String("");
}
//mBlock offline version
String TSSerial::receive(byte rx)
{
  return receive(rx, rx+1);
}
int TSSerial::receiveVariable(String label, byte rx)
{
  String com = receive(rx);
  int val=0;
  updateComVariable(com, label, val);
  return val;
}
byte TSSerial::receive()
{
  if(mSerial && mSerial->available())
  {
    return mSerial->read();
  }
  return 0;
}
bool TSSerial::dataAvailable(byte rx, byte tx)
{
  if(!mSerial) init(rx, tx);
  return mSerial->available();
}
bool TSSerial::dataAvailable(byte rx)
{
  return dataAvailable(rx, rx+1);
}
