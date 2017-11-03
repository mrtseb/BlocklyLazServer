/*************************************************** 
  This is a library for our optical Fingerprint sensor

  Designed specifically to work with the Adafruit Fingerprint sensor 
  ----> http://www.adafruit.com/products/751

  These displays use TTL Serial to communicate, 2 pins are required to 
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_Fingerprint.h"
#include <util/delay.h>

#if ARDUINO >= 100
Adafruit_Fingerprint::Adafruit_Fingerprint(SoftwareSerial *ss, int _setup)  : virtualGroveConnector() {
#else
Adafruit_Fingerprint::Adafruit_Fingerprint(NewSoftSerial *ss) {
#endif
  thePassword = 0;
  theAddress = 0xFFFFFFFF;

  mySerial = ss;
  _isAvailable = false;
  if (_setup)
  {
    begin(57600);
#ifdef DEBUG
    if (_isAvailable)
    {
      Serial.println("Found fingerprint sensor!");
    } else {
      Serial.println("Did not find fingerprint sensor :(");
    }
#endif
  }
}



void Adafruit_Fingerprint::begin(uint16_t baudrate) {
  delay(1000);  // one second delay to let the sensor 'boot up'

  mySerial->begin(baudrate);
  verifyPassword();
}

boolean Adafruit_Fingerprint::verifyPassword(void) {
 /* uint8_t packet[] = {FINGERPRINT_VERIFYPASSWORD, 
                      (thePassword >> 24), (thePassword >> 16),
                      (thePassword >> 8), thePassword};*/
  uint8_t *packet=packetBuffer;
  packet[0] = FINGERPRINT_VERIFYPASSWORD; 
  packet[1] = (thePassword >> 24); 
  packet[2] = (thePassword >> 16);
  packet[3] = (thePassword >> 8); 
  packet[4] = (thePassword);
  
  writePacket(theAddress, FINGERPRINT_COMMANDPACKET, 7, packet);
  uint8_t len = getReply(packet);
  
  if ((len == 1) && (packet[0] == FINGERPRINT_ACKPACKET) && (packet[1] == FINGERPRINT_OK))
  {
    _isAvailable = true;
    return true;
  }

/*
  Serial.print("\nGot packet type "); Serial.print(packet[0]);
  for (uint8_t i=1; i<len+1;i++) {
    Serial.print(" 0x");
    Serial.print(packet[i], HEX);
  }
  */
  return false;
}

uint8_t Adafruit_Fingerprint::deleteAllFingerprint() {
  uint8_t p = FINGERPRINT_OK;
  
  for (uint8_t id = 0; id<167; id++)
  {
    if (p==FINGERPRINT_OK)
    {
      p = this->deleteModel(id);
      delay(10);
      p = this->deleteModel(id);
      delay(10);
    }  
  } 

#ifdef DEBUG    
  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  } 
 #endif  
  return p;
}

//#define DEBUG
boolean Adafruit_Fingerprint::enrollFingerPrintPass1(uint8_t id) {
  if (!_isAvailable)
  {
    return false;
  }
  uint8_t p = -1;

#ifdef DEBUG    
  //Serial.println("Waiting for valid finger to enroll");
#endif

  while ((p != FINGERPRINT_OK) && (p != FINGERPRINT_NOFINGER)) {
    p = getImage();
#ifdef DEBUG    
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        //Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
#endif
  }

  if (p != FINGERPRINT_OK)
  {
      return false;
  }
  // OK success!
  p = image2Tz(1);
#ifdef DEBUG    
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
#else
  if (p==FINGERPRINT_OK)
  {
      return true;
  } else {
      return false;
  }
#endif
}

boolean Adafruit_Fingerprint::enrollFingerPrintPass2(uint8_t id) {
  if (!_isAvailable)
  {
    return false;
  }
  uint8_t p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = getImage();
  }

  p = -1;
#ifdef DEBUG
  Serial.println("Place same finger again");
#endif
  while (p != FINGERPRINT_OK) {
    p = getImage();
#ifdef DEBUG
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
#endif
  }

  // OK success!
  p = image2Tz(2);
#ifdef DEBUG
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
#else
  if (p!= FINGERPRINT_OK)
  {
    return false;
  }
#endif
  
  
  // OK converted!
  p = createModel();
#ifdef DEBUG
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  } 
#else 
  if (p != FINGERPRINT_OK) {
    return false;
  }
#endif  
  
  p = storeModel(id);
#ifdef DEBUG
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  } 
#else 
  if (p == FINGERPRINT_OK) 
  {
    return true;
  } else {
    return false;   
  
  }
#endif
}


uint16_t Adafruit_Fingerprint::getIDnumber2() {
  if (_isAvailable)
  { 
    uint8_t p = getImage();
    if (p != FINGERPRINT_OK)  
      return 0xFFFF;

    p = image2Tz();
    if (p != FINGERPRINT_OK)  
      return 0xFFFF;

    p = fingerFastSearch();
    if (p != FINGERPRINT_OK)  
      return 0xFFFF;
  
  // found a match!
    return fingerID;
  } else {
    return 0xFFFF;
    
  }
}

boolean Adafruit_Fingerprint::fingerAvailable() {
  if (_isAvailable)
  { 
    uint8_t p = getImage();
    if (p == FINGERPRINT_NOFINGER) 
      return true;
  }
  return false;
}
boolean Adafruit_Fingerprint::getFingerprintIDez() {
  if (_isAvailable)
  { 
    uint8_t p = getImage();
    if (p != FINGERPRINT_OK) // (p != FINGERPRINT_OK) 
      return false;

    p = image2Tz();
    if (p != FINGERPRINT_OK)  
      return false;

    p = fingerFastSearch();
    if (p != FINGERPRINT_OK)  
      return false;
  
  // found a match!
    return true;
  } else {
    return false;
    
  }
}

uint8_t Adafruit_Fingerprint::getImage(void) {
  //uint8_t packet[] = {FINGERPRINT_GETIMAGE};
  uint8_t *packet=packetBuffer;
  packet[0] =  FINGERPRINT_GETIMAGE;
  writePacket(theAddress, FINGERPRINT_COMMANDPACKET, 3, packet);
  uint8_t len = getReply(packet);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return -1;
  return packet[1];
}

uint8_t Adafruit_Fingerprint::image2Tz(uint8_t slot) {
  /*uint8_t packet[] = {FINGERPRINT_IMAGE2TZ, slot};*/
  uint8_t *packet=packetBuffer;
  packet[0] =  FINGERPRINT_IMAGE2TZ;
  packet[1] =  slot;
  writePacket(theAddress, FINGERPRINT_COMMANDPACKET, 4/*sizeof(packet)+2*/, packet);
  uint8_t len = getReply(packet);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return -1;
  return packet[1];
}


uint8_t Adafruit_Fingerprint::createModel(void) {
  /*uint8_t packet[] = {FINGERPRINT_REGMODEL};*/
  uint8_t *packet=packetBuffer;
  packet[0] =  FINGERPRINT_REGMODEL;
  writePacket(theAddress, FINGERPRINT_COMMANDPACKET, 4/*sizeof(packet)+2*/, packet);
  uint8_t len = getReply(packet);
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return -1;
  return packet[1];
}


uint8_t Adafruit_Fingerprint::storeModel(uint16_t id) {
  //uint8_t packet[] = {FINGERPRINT_STORE, 0x01, id >> 8, id & 0xFF};
  uint8_t *packet=packetBuffer;
  packet[0] = FINGERPRINT_STORE;
  packet[1] =  0x01;
  packet[2] = id >> 8;
  packet[3] = id & 0xFF;
  writePacket(theAddress, FINGERPRINT_COMMANDPACKET, 6/*sizeof(packet)+2*/, packet);
  uint8_t len = getReply(packet);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return -1;
  return packet[1];
}

uint8_t Adafruit_Fingerprint::deleteModel(uint16_t id) {
    //uint8_t packet[] = {FINGERPRINT_DELETE, id >> 8, id & 0xFF, 0x00, 0x01};
    uint8_t *packet=packetBuffer;
    packet[0] = FINGERPRINT_DELETE;
    packet[1] = id >> 8;
    packet[2] = id & 0xFF;
    packet[3] = 0x00;
    packet[4] = 0x01;
    writePacket(theAddress, FINGERPRINT_COMMANDPACKET, 7/*sizeof(packet)+2*/, packet);
    uint8_t len = getReply(packet);
        
    if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
        return -1;
    return packet[1];
}

uint8_t Adafruit_Fingerprint::emptyDatabase(void) {
  //uint8_t packet[] = {FINGERPRINT_EMPTY};
  uint8_t *packet=packetBuffer;
  packet[0] = FINGERPRINT_EMPTY;
  writePacket(theAddress, FINGERPRINT_COMMANDPACKET, 3/*sizeof(packet)+2*/, packet);
  uint8_t len = getReply(packet);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return -1;
  return packet[1];
}

uint8_t Adafruit_Fingerprint::fingerFastSearch(void) {
  fingerID = 0xFFFF;
  confidence = 0xFFFF;
  // high speed search of slot #1 starting at page 0x0000 and page #0x00A3 
  //uint8_t packet[] = {FINGERPRINT_HISPEEDSEARCH, 0x01, 0x00, 0x00, 0x00, 0xA3};
  uint8_t *packet=packetBuffer;
  packet[0] = FINGERPRINT_HISPEEDSEARCH;
  packet[1] = 0x01;
  packet[2] = 0x00;
  packet[3] = 0x00;
  packet[4] = 0x00;
  packet[5] = 0xA3;
  writePacket(theAddress, FINGERPRINT_COMMANDPACKET, 8/*sizeof(packet)+2*/, packet);
  uint8_t len = getReply(packet);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return -1;

  if (packet[1]==FINGERPRINT_OK) 
  {
      fingerID = packet[2];
      fingerID <<= 8;
      fingerID |= packet[3];
      
      confidence = packet[4];
      confidence <<= 8;
      confidence |= packet[5];
  }
  
  return packet[1];
}

uint8_t Adafruit_Fingerprint::getTemplateCount(void) {
  templateCount = 0xFFFF;
  // get number of templates in memory
  //uint8_t packet[] = {FINGERPRINT_TEMPLATECOUNT};
  uint8_t *packet=packetBuffer;
  packet[0] = FINGERPRINT_TEMPLATECOUNT;
  writePacket(theAddress, FINGERPRINT_COMMANDPACKET, 3/*sizeof(packet)+2*/, packet);
  uint8_t len = getReply(packet);
  
  if ((len != 1) && (packet[0] != FINGERPRINT_ACKPACKET))
   return -1;

  templateCount = packet[2];
  templateCount <<= 8;
  templateCount |= packet[3];
  
  return packet[1];
}



void Adafruit_Fingerprint::writePacket(uint32_t addr, uint8_t packettype, 
               uint16_t len, uint8_t *packet) {
#ifdef FINGERPRINT_DEBUG
  Serial.print("---> 0x");
  Serial.print((uint8_t)(FINGERPRINT_STARTCODE >> 8), HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)FINGERPRINT_STARTCODE, HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)(addr >> 24), HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)(addr >> 16), HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)(addr >> 8), HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)(addr), HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)packettype, HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)(len >> 8), HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)(len), HEX);
#endif
 
#if ARDUINO >= 100
  mySerial->write((uint8_t)(FINGERPRINT_STARTCODE >> 8));
  mySerial->write((uint8_t)FINGERPRINT_STARTCODE);
  mySerial->write((uint8_t)(addr >> 24));
  mySerial->write((uint8_t)(addr >> 16));
  mySerial->write((uint8_t)(addr >> 8));
  mySerial->write((uint8_t)(addr));
  mySerial->write((uint8_t)packettype);
  mySerial->write((uint8_t)(len >> 8));
  mySerial->write((uint8_t)(len));
#else
  mySerial->print((uint8_t)(FINGERPRINT_STARTCODE >> 8), BYTE);
  mySerial->print((uint8_t)FINGERPRINT_STARTCODE, BYTE);
  mySerial->print((uint8_t)(addr >> 24), BYTE);
  mySerial->print((uint8_t)(addr >> 16), BYTE);
  mySerial->print((uint8_t)(addr >> 8), BYTE);
  mySerial->print((uint8_t)(addr), BYTE);
  mySerial->print((uint8_t)packettype, BYTE);
  mySerial->print((uint8_t)(len >> 8), BYTE);
  mySerial->print((uint8_t)(len), BYTE);
#endif
  
  uint16_t sum = (len>>8) + (len&0xFF) + packettype;
  for (uint8_t i=0; i< len-2; i++) {
#if ARDUINO >= 100
    mySerial->write((uint8_t)(packet[i]));
#else
    mySerial->print((uint8_t)(packet[i]), BYTE);
#endif
#ifdef FINGERPRINT_DEBUG
    Serial.print(" 0x"); Serial.print(packet[i], HEX);
#endif
    sum += packet[i];
  }
#ifdef FINGERPRINT_DEBUG
  //Serial.print("Checksum = 0x"); Serial.println(sum);
  Serial.print(" 0x"); Serial.print((uint8_t)(sum>>8), HEX);
  Serial.print(" 0x"); Serial.println((uint8_t)(sum), HEX);
#endif
#if ARDUINO >= 100
  mySerial->write((uint8_t)(sum>>8));
  mySerial->write((uint8_t)sum);
#else
  mySerial->print((uint8_t)(sum>>8), BYTE);
  mySerial->print((uint8_t)sum, BYTE);
#endif
}


uint8_t Adafruit_Fingerprint::getReply(uint8_t packet[], uint16_t timeout) {
  uint8_t reply[20], idx;
  uint16_t timer=0;
  
  idx = 0;
#ifdef FINGERPRINT_DEBUG
  Serial.print("<--- ");
#endif
while (true) {
    while (!mySerial->available()) {
      delay(1);
      timer++;
      if (timer >= timeout) return FINGERPRINT_TIMEOUT;
    }
    // something to read!
    reply[idx] = mySerial->read();
#ifdef FINGERPRINT_DEBUG
    Serial.print(" 0x"); Serial.print(reply[idx], HEX);
#endif
    if ((idx == 0) && (reply[0] != (FINGERPRINT_STARTCODE >> 8)))
      continue;
    idx++;
    
    // check packet!
    if (idx >= 9) {
      if ((reply[0] != (FINGERPRINT_STARTCODE >> 8)) ||
          (reply[1] != (FINGERPRINT_STARTCODE & 0xFF)))
          return FINGERPRINT_BADPACKET;
      uint8_t packettype = reply[6];
      //Serial.print("Packet type"); Serial.println(packettype);
      uint16_t len = reply[7];
      len <<= 8;
      len |= reply[8];
      len -= 2;
      //Serial.print("Packet len"); Serial.println(len);
      if (idx <= (len+10)) continue;
      packet[0] = packettype;      
      for (uint8_t i=0; i<len; i++) {
        packet[1+i] = reply[9+i];
      }
#ifdef FINGERPRINT_DEBUG
      Serial.println();
#endif
      return len;
    }
  }
}

