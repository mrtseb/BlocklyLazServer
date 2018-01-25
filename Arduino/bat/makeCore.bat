@echo off
REM CONFIGURATION
SET prefix=.
SET AVR_CPP=%prefix%\hardware\tools\avr\bin\avr-g++.exe
SET AVR_GCC=%prefix%\hardware\tools\avr\bin\avr-gcc.exe  
SET AVR_AR=%prefix%\hardware\tools\avr\bin\avr-gcc-ar.exe
SET AVR_AS=%prefix%\hardware\tools\avr\bin\avr-as.exe
SET AVR_RANLIB=%prefix%\hardware\tools\avr\bin\avr-ranlib.exe
SET dir=%prefix%\hardware\arduino\avr
SET ldir=%prefix%\libraries
SET ts=%ldir%\TS
SET ultra=%ldir%\Ultrasonic
SET mb=%ldir%\makeblock\src
SET ldir2=%prefix%\hardware\arduino\avr\libraries
SET ir_remote=%ldir%\IRremote
SET ethernet=%ldir%\Ethernet\src
SET bmp280=%ldir%\BMP280
ECHO %time%
DEL %prefix%\core\*.* /q

ECHO "GENERATION DE SPI"
for %%v in ( %ldir2%\SPI\src\*.cpp ) do (
  ECHO %%v
  %AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%dir%\variants\standard -I%ldir2%/Wire -I%ldir2%/Wire/utility/ -I%ldir2%/SPI/src -o %%v.o %%v
)

for %%v in ( %ldir2%\SPI\src\*.o ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

for %%v in ( %ldir2%\SPI\src\*.d ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

ECHO "GENERATION DE ETHERNET UTILITY"
for %%v in ( %ethernet%\utility\*.cpp ) do (
  ECHO %%v
  %AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%ultra% -I%dir%\variants\standard -I%ldir2%/SPI/src -I%ethernet% -I%ethernet%/utility -o %%v.o %%v
)

for %%v in ( %ethernet%\utility\*.o ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

for %%v in ( %ethernet%\utility\*.d ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)


ECHO "GENERATION DE ETHERNET"
for %%v in ( %ethernet%\*.cpp ) do (
  ECHO %%v
  %AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%ultra% -I%dir%\variants\standard -I%ldir2%/SPI/src -I%ethernet% -I%ethernet%/utility -o %%v.o %%v
)

for %%v in ( %ethernet%\*.o ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

for %%v in ( %ethernet%\*.d ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

ECHO "GENERATION DE ULTRASONIC"
for %%v in ( %ultra%\*.cpp ) do (
  ECHO %%v
  %AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%ultra% -I%dir%\variants\standard -o %%v.o %%v
)

for %%v in ( %ultra%\*.o ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

for %%v in ( %ultra%\*.d ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)


ECHO "GENERATION DE IR_REMOTE"
for %%v in ( %ir_remote%\*.cpp ) do (
  ECHO %%v
  %AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%dir%\variants\standard -o %%v.o %%v
)

for %%v in ( %ir_remote%\*.o ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

for %%v in ( %ir_remote%\*.d ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)



ECHO "GENERATION DE BMP280"
for %%v in ( %bmp280%\*.cpp ) do (
  ECHO %%v
  %AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%dir%\variants\standard -I%ldir2%/Wire -I%ldir2%/Wire/utility/ -I%ldir2%/SPI/src -I%bmp280% -o %%v.o %%v
)

for %%v in ( %bmp280%\*.o ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

for %%v in ( %bmp280%\*.d ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)


ECHO "GENERATION DE WIRE_PULSE ASM"
%AVR_GCC% -c -g -x assembler-with-cpp -flto -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%/cores/arduino -I%dir%/variants/standard -o core/wiring_pulse.S.o %dir%\cores\arduino\wiring_pulse.S
ECHO "COMPILATION DES FICHIERS CORE ARDUINO"
for %%v in ( %dir%\cores\arduino\*.c ) do (
  ECHO %%v
  %AVR_GCC% -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%dir%\variants\standard -o %%v.o %%v
)
for %%v in ( %dir%\cores\arduino\*.cpp ) do (
  ECHO %%v
  %AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%dir%\variants\standard -o %%v.o %%v
)

for %%v in ( %dir%\cores\arduino\*.o ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

for %%v in ( %dir%\cores\arduino\*.d ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

ECHO "Compilation de la lib TS"
for %%v in ( %ts%\*.cpp ) do (
  ECHO %%v
  %AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%dir%\variants\standard -I%ts% -I%ldir2%/Wire -I%ldir2%/Wire/utility/ -I%ldir2%/SoftwareSerial -o %%v.o %%v
)

for %%v in ( %ts%\*.o ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

for %%v in ( %ts%\*.d ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)


ECHO "Compilation de makeblock"
for %%v in ( %mb%\*.cpp ) do (
  ECHO %%v
  %AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%\cores\arduino -I%dir%\variants\standard -I%ts% -I%ldir2%/Wire -I%ldir2%/Wire/utility/ -I%ldir2%/SoftwareSerial -I%mb% -o %%v.o %%v
)

for %%v in ( %mb%\*.o ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)

for %%v in ( %mb%\*.d ) do (
  ECHO %%v  
  MOVE %%v  ./core/
)


ECHO "GENERATION DE SOFTSERIAL"
%AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%/cores/arduino -I%dir%/variants/standard -I%ldir2%/SoftwareSerial -o core/SoftwareSerial.o %ldir2%/SoftwareSerial/SoftwareSerial.cpp
echo "Génération de TWI WIRE"
%AVR_GCC% -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%/cores/arduino -I%dir%/variants/standard -I%ldir2%/Wire -I%ldir2%/Wire/utility/ -o core/twi.o %ldir2%/Wire/utility/twi.c
echo "Génération de WIRE"
%AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%/cores/arduino -I%dir%/variants/standard -I%ldir2%/Wire -I%ldir2%/Wire/utility/ -o core/Wire.o %ldir2%/Wire/Wire.cpp
ECHO "Génération de SERVO"
%AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%/cores/arduino -I%dir%/variants/standard -I %ldir%/Servo/src/ -o core/Servo.o %ldir%/Servo/src/avr/Servo.cpp
ECHO "Génération de FIRMATA"
%AVR_CPP% -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10801 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -I%dir%/cores/arduino -I%dir%/variants/standard -I %ldir%/Firmata/ -I %ldir%/Firmata/utility/ -o core/Firmata.o %ldir%/Firmata/Firmata.cpp
ECHO "ASSEMBLAGE DE LA BIBLIOTHEQUE"
%AVR_AR% rcsv core/core.a core/*.o
echo %time%
:eof

