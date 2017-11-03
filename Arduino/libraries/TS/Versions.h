//Uno
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
  #define INCLUDE_LEDSTRIP
//MEGA
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  #define INCLUDE_JEULIN
  #define INCLUDE_LEDSTRIP
  #define INCLUDE_MP3PLAYER
  #define INCLUDE_BMP280
#endif
