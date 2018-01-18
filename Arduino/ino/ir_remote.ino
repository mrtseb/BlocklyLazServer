#include <IRremote.h>
#include "makeblock_codes.h"

IRrecv irrecv(2);
decode_results signals;



void setup()
{
    //pinMode(13, OUTPUT);
    irrecv.enableIRIn();
}

void loop() {
if (irrecv.decode(&signals)) {

    unsigned int value = signals.value;

    if (value==codeA) {
        //digitalWrite(13, HIGH);   // turn it off when button is pressed
    }

    irrecv.resume();
 }
}