#ifndef TSLEDSTRIP
#define TSLEDSTRIP


#include "Adafruit_NeoPixel.h"
#include "virtualGroveConnector.h"

#define FULL      0
#define FADE      1
#define RAINBOW1  2
#define RAINBOW2  3
#define VOGUE     4
#define CYLON     5
#define CASCADE   6


class TSLedStrip : public virtualGroveConnector
{
  public:
    TSLedStrip() : mState(0), mDelay(100), mStrip(0), virtualGroveConnector() {
      ;
    }

    void init(byte pin, byte leds)
    {
      if (!mStrip)
      {
        mStrip = new Adafruit_NeoPixel(leds, pin, NEO_GRB + NEO_KHZ800);
        mStrip->begin();
        mStrip->show();
      }
    }
    byte mState;
    Adafruit_NeoPixel* mStrip;
    unsigned int mDelay;

    void animation(byte pattern, byte r, byte g, byte b)
    {
      switch (pattern)
      {
        case FULL:
          clearLEDs(mStrip->Color(r, g, b));
          mStrip->show();
          break;
        case FADE:
          colorWipe(mStrip->Color(r, g, b), mDelay);
          break;
        case RAINBOW1:
          rainbow();
          break;
        case RAINBOW2:
          rainbowCycle();
          break;
        case VOGUE:
          theaterChaseRainbow();
          break;
        case CYLON:
          cylon(mStrip->Color(r, g, b));
          break;
        case CASCADE:
          cascade(mStrip->Color(r, g, b));
          break;
      }
      mState++;
    }
  private:
    //Theatre-style crawling lights with rainbow effect
    void theaterChaseRainbow() {
      for (int q = 0; q < 3; q++) {
        for (uint16_t i = 0; i < mStrip->numPixels(); i = i + 3) {
          mStrip->setPixelColor(i + q, Wheel( (i + mState) % 255)); //turn every third pixel on
        }
        mStrip->show();

        delay(mDelay);

        for (uint16_t i = 0; i < mStrip->numPixels(); i = i + 3) {
          mStrip->setPixelColor(i + q, 0);      //turn every third pixel off
        }

      }
    }

    void rainbow() {
      uint16_t i;

      for (i = 0; i < mStrip->numPixels(); i++) {
        mStrip->setPixelColor(i, Wheel((i + mState) & 255));
      }
      mStrip->show();
    }

    void rainbowCycle() {
      uint16_t i;

      for (i = 0; i < mStrip->numPixels(); i++) {
        mStrip->setPixelColor(i, Wheel(((i * 256 / mStrip->numPixels()) + mState) & 255));
      }
      mStrip->show();
    }

    void cylon(unsigned long color)
    {
      // weight determines how much lighter the outer "eye" colors are
      const byte weight = 4;
      // It'll be easier to decrement each of these colors individually
      // so we'll split them out of the 24-bit color value
      byte red = (color & 0xFF0000) >> 16;
      byte green = (color & 0x00FF00) >> 8;
      byte blue = (color & 0x0000FF);

      // Start at closest LED, and move to the outside
      for (int i = 0; i <= mStrip->numPixels() - 1; i++)
      {
        clearLEDs(0);
        mStrip->setPixelColor(i, red, green, blue);  // Set the bright middle eye
        // Now set two eyes to each side to get progressively dimmer
        for (int j = 1; j < 3; j++)
        {
          if (i - j >= 0)
            mStrip->setPixelColor(i - j, red / (weight * j), green / (weight * j), blue / (weight * j));
          if (i - j <= mStrip->numPixels())
            mStrip->setPixelColor(i + j, red / (weight * j), green / (weight * j), blue / (weight * j));
        }
        mStrip->show();  // Turn the LEDs on
        delay(mDelay);  // Delay for visibility
      }

      // Now we go back to where we came. Do the same thing.
      for (int i = mStrip->numPixels() - 2; i >= 1; i--)
      {
        clearLEDs(0);
        mStrip->setPixelColor(i, red, green, blue);
        for (int j = 1; j < 3; j++)
        {
          if (i - j >= 0)
            mStrip->setPixelColor(i - j, red / (weight * j), green / (weight * j), blue / (weight * j));
          if (i - j <= mStrip->numPixels())
            mStrip->setPixelColor(i + j, red / (weight * j), green / (weight * j), blue / (weight * j));
        }

        mStrip->show();
        delay(mDelay);
      }
    }
    // Cascades a single direction. One time.
    void cascade(unsigned long color)
    {
      for (int i = 0; i < mStrip->numPixels(); i++)
      {
        clearLEDs(0);  // Turn off all LEDs
        mStrip->setPixelColor(i, color);  // Set just this one
        mStrip->show();
        delay(mDelay);
      }
    }
    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos) {
      WheelPos = 255 - WheelPos;
      if (WheelPos < 85) {
        return mStrip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
      }
      if (WheelPos < 170) {
        WheelPos -= 85;
        return mStrip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
      }
      WheelPos -= 170;
      return mStrip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }

    // Fill the dots one after the other with a color
    void colorWipe(uint32_t c, uint8_t wait) {
      for (uint16_t i = 0; i < mStrip->numPixels(); i++) {
        mStrip->setPixelColor(i, c);
        mStrip->show();
        delay(wait);
      }
    }

    void clearLEDs(uint32_t color)
    {
      for (int i = 0; i < mStrip->numPixels(); i++)
      {
        mStrip->setPixelColor(i, color);
      }
    }

};

#endif
