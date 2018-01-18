@ECHO OFF
CLS
set NLM=^


set NL=^^^%NLM%%NLM%^%NLM%%NLM%
SET projet=Marlin-Firmwares_E200_1495568437_3693ab75a05ca48acdb9d3a15d9fc431
SET serie=COM6
SET baud=9600
SET prefix=.
SET dir=%prefix%\hardware\arduino\avr
SET ldir=%prefix%\libraries
SET AVR_DUDE=%prefix%\hardware\tools\avr\bin\avrdude.exe
SET depart=%time%
ECHO "TELEVERSEMENT DU FICHIER HEX VERS ARDUINO SUR %serie% A LA VITESSE %baud%"
%AVR_DUDE% -v -patmega328p -carduino -P%serie% -Chardware\tools\avr\etc\avrdude.conf -D -Uflash:w:.\prod\%projet%.hex:i


echo %depart% - %time%
