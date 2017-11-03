/*
*Library Technologie Services
* Copyright © 2016 by Technologie Services. All rights reserved
Version 1
<http://www.technologieservices.fr>
*/

#ifndef TSSerial_H
#define TSSerial_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class TSSerial
{
	public:
	TSSerial();
  void init(byte rx, byte tx, unsigned long speed);
  bool dataAvailable(byte rx, byte tx);
  bool dataAvailable(byte rx);
	void send(byte, byte, String);
	void send(byte, String);
	String receive(byte, byte);
  String receive(byte);
  int receive(byte rx, String label);
  int receiveVariable(String label, byte rx);
	byte receive();
  
  private:
  SoftwareSerial *mSerial;
  byte mTx;
  byte mRx;
};

#endif
