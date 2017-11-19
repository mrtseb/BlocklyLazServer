@ECHO OFF
CLS
set NLM=^


set NL=^^^%NLM%%NLM%^%NLM%%NLM%
SET projet=%userdomain%_%username%_default
SET serie=%1
SET baud=%2
SET prefix=.
SET dir=%prefix%\hardware\arduino\avr
SET ldir=%prefix%\libraries
SET AVR_DUDE=%prefix%\hardware\tools\avr\bin\avrdude.exe
SET depart=%time%
ECHO "TELEVERSEMENT DU FICHIER HEX VERS ARDUINO SUR %serie% A LA VITESSE %baud%"
%AVR_DUDE% -v -patmega328p -carduino -P%serie% -b%baud% -Chardware\tools\avr\etc\avrdude.conf -D -Uflash:w:.\prod\%projet%.hex:i


echo %depart% - %time%
