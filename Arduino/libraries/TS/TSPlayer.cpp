/*
   MP3Player_KT403A.cpp
   A library for Grove-Serial MP3 Player V2.0

   Copyright (c) 2015 seeed technology inc.
   Website    : www.seeed.cc
   Author     : Wuruibin
   Created Time: Dec 2015
   Modified Time:

   The MIT License (MIT)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <Arduino.h>
#include "TSPlayer.h"

TSPlayer::TSPlayer() : mSerial(0), virtualGroveConnector()
{

}

void TSPlayer::init(byte pin)
{
  if (!mSerial)
  {
    mSerial = new SoftwareSerial(pin, pin + 1);
  }
  mSerial->begin(9600);
  delay(100);
  SelectPlayerDevice(0x02);       // Select SD card as the player device.
  SetVolume(0x0E);
}

void TSPlayer::command(byte com)
{
  switch (com)
  {
    case 1:
      SpecifyMusicPlay(1);
      //Serial.println("Specify the music index to play");
      break;
    case 2:
      PlayPause();
      //Serial.println("Pause the MP3 player");
      break;
    case 3:
      PlayResume();
      //Serial.println("Resume the MP3 player");
      break;
    case 4:
      PlayNext();
      //Serial.println("Play the next song");
      break;
    case 5:
      PlayPrevious();
      //Serial.println("Play the previous song");
      break;
    case 6:
      PlayLoop();
      //Serial.println("Play loop for all the songs");
      break;
    case 7:
      IncreaseVolume();
      //Serial.println("Increase volume");
      break;
    case 8:
      DecreaseVolume();
      //Serial.println("Decrease volume");
  }
}
/****************************************************************
   Function Name: SelectPlayerDevice
   Description: Select the player device, U DISK or SD card.
   Parameters: 0x01:U DISK;  0x02:SD card
   Return: none
****************************************************************/
void TSPlayer::SelectPlayerDevice(uint8_t device)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x09);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(device);
  mSerial->write(0xEF);
  delay(200);
}

/****************************************************************
   Function Name: SpecifyMusicPlay
   Description: Specify the music index to play, the index is decided by the input sequence of the music.
   Parameters: index: the music index: 0-65535.
   Return: none
****************************************************************/
void TSPlayer::SpecifyMusicPlay(uint16_t index)
{
  uint8_t hbyte, lbyte;
  hbyte = index / 256;
  lbyte = index % 256;
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x03);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(hbyte));
  mSerial->write(uint8_t(lbyte));
  mSerial->write(0xEF);
  delay(10);
  //  return true;
}

/****************************************************************
   Function Name: SpecifyfolderPlay
   Description: Specify the music index in the folder to play, the index is decided by the input sequence of the music.
   Parameters: folder: folder name, must be number;  index: the music index.
   Return: none
****************************************************************/
void TSPlayer::SpecifyfolderPlay(uint8_t folder, uint8_t index)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x0F);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(folder));
  mSerial->write(uint8_t(index));
  mSerial->write(0xEF);
  delay(10);
  //  return true;
}

/****************************************************************
   Function Name: PlayPause
   Description: Pause the MP3 player.
   Parameters: none
   Return: none
****************************************************************/
void TSPlayer::PlayPause(void)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x0E);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  //  mSerial->write(0xFE);
  //  mSerial->write(0xED);
  mSerial->write(0xEF);
  delay(20);
  //  return true;
}

/****************************************************************
   Function Name: PlayResume
   Description: Resume the MP3 player.
   Parameters: none
   Return: none
****************************************************************/
void TSPlayer::PlayResume(void)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x0D);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  //  mSerial->write(0xFE);
  //  mSerial->write(0xEE);
  mSerial->write(0xEF);
  delay(20);
  //  return true;
}

/****************************************************************
   Function Name: PlayNext
   Description: Play the next song.
   Parameters: none
   Return: none
****************************************************************/
void TSPlayer::PlayNext(void)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x01);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(0xEF);
  delay(10);
  //  return true;
}

/****************************************************************
   Function Name: PlayPrevious
   Description: Play the previous song.
   Parameters: none
   Return: none
****************************************************************/
void TSPlayer::PlayPrevious(void)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x02);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(0xEF);
  delay(10);
  //  return true;
}

/****************************************************************
   Function Name: PlayLoop
   Description: Play loop for all the songs.
   Parameters: none
   Return: none
****************************************************************/
void TSPlayer::PlayLoop(void)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x11);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(0x01);
  mSerial->write(0xEF);
  delay(10);
  //  return true;
}

/****************************************************************
   Function Name: SetVolume
   Description: Set the volume, the range is 0x00 to 0x1E.
   Parameters: volume: the range is 0x00 to 0x1E.
   Return: none
****************************************************************/
void TSPlayer::SetVolume(uint8_t volume)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x06);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(volume);
  mSerial->write(0xEF);
  delay(10);
  //  return true;
}

/****************************************************************
   Function Name: IncreaseVolume
   Description: Increase the volume.
   Parameters: none
   Return: none
****************************************************************/
void TSPlayer::IncreaseVolume(void)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x04);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(0xEF);
  delay(10);
  //  return true;
}

/****************************************************************
   Function Name: DecreaseVolume
   Description: Decrease the volume.
   Parameters: none
   Return: none
****************************************************************/
void TSPlayer::DecreaseVolume(void)
{
  mSerial->write(0x7E);
  mSerial->write(0xFF);
  mSerial->write(0x06);
  mSerial->write(0x05);
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(uint8_t(0x00));
  mSerial->write(0xEF);
  delay(10);
  //  return true;
}



/****************************************************************
   Function Name: printReturnedData
   Description: Print the returned data that sent from the Grove_Serial_MP3_Player.
   Parameters: none
   Return: none
****************************************************************/
/*
  void TSPlayer::printReturnedData(void)
  {
     unsigned char c;
    //check if there's any data sent from the Grove_Serial_MP3_Player
    while(mSerial->available())
    {
        c = mSerial->read();
        Serial.print("0x");
        Serial.print(c, HEX);
        Serial.print(" ");
    }
    Serial.println(" ");
  }
*/
/****************************************************************
   Function Name: QueryPlayStatus
   Description: Query play status.
   Parameters: none
   Return: 0: played out; 1: other.
   Usage: while(QueryPlayStatus() != 0);  // Waiting to play out.
****************************************************************/
/*uint8_t TSPlayer::QueryPlayStatus(void)
  {
    unsigned char c[10] = {0};
    uint8_t i = 0;
    //check if there's any data sent from the Grove_Serial_MP3_Player
    while(mSerial->available())
    {
        c[i] = mSerial->read();
        i++;
		delay(1);
		if (i == 10) break;
  //        Serial.print(" 0x");
  //        Serial.print(c[i], HEX);
    }
  //    Serial.println(" ");

    if(c[3] == 0x3C || c[3] == 0x3D || c[3] == 0x3E)
    {
        return 0;
    }
    else
    {
        return 1;
    }
  }*/
