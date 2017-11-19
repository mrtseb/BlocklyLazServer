/**
 * @license Licensed under the Apache License, Version 2.0 (the "License"):
 *          http://www.apache.org/licenses/LICENSE-2.0
 */

/**
 * @fileoverview Code generator for Arduino Digital and Analogue input/output.
 *     Arduino built in function docs: http://arduino.cc/en/Reference/HomePage
 */
'use strict';

goog.provide('Blockly.Arduino.grove');

goog.require('Blockly.Arduino');
//rem unixtime = time en s depuis 01/01/1970
// si (now.unixtime - depart.unixtime) % 1 = 0 alors 1 SEC DE PASSEE
// si (now.unixtime - depart.unixtime) % 60 = 0 alors 1 MIN DE PASSEE
// si (now.unixtime - depart.unixtime) % 60*60 = 0 alors 1 H DE PASSEE
   
Blockly.Arduino.grove_rtc = function(block) {
	
	Blockly.Arduino.definitions_['define_rtclib_current'] = 'long currentTime;\n';
	Blockly.Arduino.definitions_['define_rtclib_lasttime'] = 'double lastTime;\n';
	Blockly.Arduino.definitions_['define_rtclib_getlasttime'] = 'long getLastTime(){\n' +
	'  return currentTime = (long) (millis()/1000.0 - lastTime);\n'+
	'}\n';
	
    Blockly.Arduino.setups_['setup_rtclib_setLastTime'] ='lastTime= millis()/1000.0;\n';
	
	
	var timing = this.getFieldValue('TIMING');
    var times = Blockly.Arduino.valueToCode(this, 'TIMES', Blockly.Arduino.ORDER_UNARY_POSTFIX) || 'S';
    var branch = Blockly.Arduino.statementToCode(block, 'DO');
    var plus;
      if (timing == 'S') {
	    plus = times*1;
      }
      if (timing=='M') {
	    plus = times*60;
      }
      if (timing=='H') {
	    plus = times*60*60;
      }

  var code = 
'currentTime = getLastTime();\n'+
'if (currentTime % ('+plus+') == 0) {\n' +
branch +
'}\n';  
  
  return code;
	
}   
   
   
Blockly.Arduino.grove_rtc2 = function(block) {
  
  Blockly.Arduino.definitions_['define_rtclib_wire'] = '#include <wire.h>;\n';
  Blockly.Arduino.definitions_['define_rtclib'] = '#include "RTClib.h";\n';
  Blockly.Arduino.definitions_['define_rtclib_var'] = 'RTC_DS1307 rtc;\n';
  Blockly.Arduino.definitions_['define_rtclib_now'] = 'DateTime now;\n';
  Blockly.Arduino.definitions_['define_rtclib_depart'] = 'DateTime depart;\n';
    
  Blockly.Arduino.setups_['setup_rtclib_begin'] = 
'if (! rtc.begin()) {\n' +
//'    Serial.println("Couldn\'t find RTC");\n' +
'    while (1);\n' +
'  }\n' +
'  if (! rtc.isrunning()) {\n' +
'    rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));\n' +
'  }\n'+
'  else {\n' +
'    depart = rtc.now();\n' +	
'  }\n'; 
  var timing = this.getFieldValue('TIMING');
  var times = Blockly.Arduino.valueToCode(this, 'TIMES', Blockly.Arduino.ORDER_UNARY_POSTFIX) || 'S';
  var branch = Blockly.Arduino.statementToCode(block, 'DO');
  var plus;
  if (timing == 'S') {
	plus = times*1;
  }
  if (timing=='M') {
	plus = times*60;
  }
  if (timing=='H') {
	plus = times*60*60;
  }

  var code = 
'now = rtc.now();\n'+
'if ((now.unixtime() - depart.unixtime()) % ('+plus+') == 0) {\n' +
branch +
'}\n';  
  
  return code;
}

Blockly.Arduino.grove_rtc_config = function(block) {
  
  Blockly.Arduino.definitions_['define_rtclib_wire'] = '#include <wire.h>;\n';
  Blockly.Arduino.definitions_['define_rtclib'] = '#include "RTClib.h";\n';
  Blockly.Arduino.definitions_['define_rtclib_var'] = 'RTC_DS1307 rtc;\n';
  
  Blockly.Arduino.setups_['setup_rtclib_begin'] = 
'if (! rtc.begin()) {\n' +
//'    Serial.println("Couldn\'t find RTC");\n' +
'    while (1);\n' +
'  }\n' +
'  if (! rtc.isrunning()) {\n' +
'    rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));\n' +
'  }\n';
var code='DateTime now = rtc.now();\n';
return code;
}

Blockly.Arduino.grove_rtc_get = function(block) {
  

  var timing = this.getFieldValue('TIMING');
  var code;
  if (timing=='J') {
	  code = 'now.day()';
  } else if (timing=='O') {
	  code = 'now.month()';
  } else if (timing=='A') {
	  code = 'now.year()';
  } else if (timing=='H') {
	  code = 'now.hour()';
  } else if (timing=='M') {
	  code = 'now.minute()';
  } else if (timing=='S') {
	  code = 'now.second()';
  }
  
  return [code, Blockly.Arduino.ORDER_UNARY_POSTFIX];
}



Blockly.Arduino.grove_led = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var dropdown_stat = this.getFieldValue('STAT');
  Blockly.Arduino.setups_['setup_green_led_'+dropdown_pin] = 'pinMode('+dropdown_pin+', OUTPUT);';
  var code = 'digitalWrite('+dropdown_pin+','+dropdown_stat+');\n'
  return code;
};

Blockly.Arduino.grove_button = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  Blockly.Arduino.setups_['setup_button_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  var code = 'digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.grove_dht11 = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  Blockly.Arduino.definitions_['define_dht11'] = '#include "DHT.h"\n';
  Blockly.Arduino.definitions_['define_dht_mode'] = 'DHT dht'+dropdown_pin+'('+dropdown_pin+', 11);\n';
  var dropdown_mes = this.getFieldValue('MESURE');
  Blockly.Arduino.setups_['setup_button_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  var code;
  if (dropdown_mes == 'temp') {
	  code = 'dht'+dropdown_pin+'.readTemperature()';
  }
  if (dropdown_mes == 'hum') {
	  code = 'dht'+dropdown_pin+'.readHumidity()';
  }
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.grove_rotary_angle = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var code = 'analogRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.grove_tilt_switch = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  Blockly.Arduino.setups_['setup_tilt_switch_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  var code = 'digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*
int buttonPin = 1;
int buzzerPin = 2;

char notes[] = "cdefgabC "; // a space represents a rest
const int length = sizeof(notes); // the number of notes
int beats[length] = { 1,1,1,1,1,1,1,1,1};

int tempo = 300;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < length; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin,INPUT);
}

void loop() {
  if(digitalRead(buttonPin))
  {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 20);
  }
  }
}
*/
Blockly.Arduino.grove_piezo_buzzer = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var dropdown_stat = this.getFieldValue('STAT');
  Blockly.Arduino.setups_['setup_piezo_buzzer_'+dropdown_pin] = 'pinMode('+dropdown_pin+', OUTPUT);';
  var code = 'digitalWrite('+dropdown_pin+','+dropdown_stat+');\n'
  return code;
};

Blockly.Arduino.grove_relay = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var dropdown_stat = this.getFieldValue('STAT');
  Blockly.Arduino.setups_['setup_relay_'+dropdown_pin] = 'pinMode('+dropdown_pin+', OUTPUT);';
  var code = 'digitalWrite('+dropdown_pin+','+dropdown_stat+');\n'
  return code;
};

Blockly.Arduino.grove_temporature_sensor = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  /*
  a=analogRead(0);
  resistance=(float)(1023-a)*10000/a;
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;
  */
  var code = 'round('+'(1/(log((float)(1023-analogRead('+dropdown_pin+'))*10000/analogRead('+dropdown_pin+'))/10000)/3975+1/298.15)-273.15'+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*
#include <SerialLCD.h>
#include <SoftwareSerial.h> //this is a must
SerialLCD slcd(11,12);//this is a must, assign soft serial pins

void setup()
{
  slcd.begin();// set up :
}

void loop()
{
  slcd.backlight();// Turn on the backlight: //noBacklight
  slcd.setCursor(0,0); // set the cursor to (0,0):
  slcd.print("  Seeed Studio"); // Print a message to the LCD.
  slcd.setCursor(0,1); //line 2
  slcd.print("   Starter kit   ");
  delay(5000);
  //slcd.scrollDisplayLeft();//scrollDisplayRight/autoscroll/
  //slcd.clear();
  //Power/noPower
}
*/

var _get_next_pin = function(dropdown_pin) {
  var NextPIN = dropdown_pin;
  if(parseInt(NextPIN)){
    NextPIN = parseInt(dropdown_pin)+1;
  } else {
    NextPIN = 'A'+(parseInt(NextPIN.slice(1,NextPIN.length))+1);
  }
  //check if NextPIN in bound
  var pinlen = profile.default.digital.length;
  var notExist=true;
  for(var i=0;i<pinlen;i++){
    if(profile.default.digital[i][1] == NextPIN){
      notExist=false;
    }
  }
  if(notExist){
    alert("Grove Sensor needs PIN#+1 port, current setting is out of bound.");
    return null;
  } else {
    return NextPIN;
  }
}

Blockly.Arduino.grove_serial_lcd_print = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var text = Blockly.Arduino.valueToCode(this, 'TEXT',
      Blockly.Arduino.ORDER_UNARY_POSTFIX) || '\'\'';
  var text2 = Blockly.Arduino.valueToCode(this, 'TEXT2',
      Blockly.Arduino.ORDER_UNARY_POSTFIX) || '\'\'';
  var delay_time = Blockly.Arduino.valueToCode(this, 'DELAY_TIME', Blockly.Arduino.ORDER_ATOMIC) || '1000';
  /*if(text.length>16||text2.length>16){
      alert("string is too long");
  }*/
  Blockly.Arduino.definitions_['define_seriallcd'] = '#include <SerialLCD.h>\n';
  Blockly.Arduino.definitions_['define_softwareserial'] = '#include <SoftwareSerial.h>\n';
  //generate PIN#+1 port
  var NextPIN = _get_next_pin(dropdown_pin);

  Blockly.Arduino.definitions_['var_lcd_'+dropdown_pin] = 'SerialLCD slcd_'+dropdown_pin+'('+dropdown_pin+','+NextPIN+');\n';

  Blockly.Arduino.setups_['setup_lcd_'+dropdown_pin] = 'slcd_'+dropdown_pin+'.begin();\n';
  var code = 'slcd_'+dropdown_pin+'.backlight();\n';
  code    += 'slcd_'+dropdown_pin+'.setCursor(0,0);\n';
  code    += 'slcd_'+dropdown_pin+'.print('+text+');\n';//text.replace(new RegExp('\'',"gm"),'')
  code    += 'slcd_'+dropdown_pin+'.setCursor(0,1);\n';
  code    += 'slcd_'+dropdown_pin+'.print('+text2+');\n';
  code    += 'delay('+delay_time+');\n';
  return code;
};

Blockly.Arduino.grove_serial_lcd_iic = function() {
  
  var text = Blockly.Arduino.valueToCode(this, 'TEXT',
      Blockly.Arduino.ORDER_UNARY_POSTFIX) || '\'\'';
  var text2 = Blockly.Arduino.valueToCode(this, 'TEXT2',
      Blockly.Arduino.ORDER_UNARY_POSTFIX) || '\'\'';
  var delay_time = Blockly.Arduino.valueToCode(this, 'DELAY_TIME', Blockly.Arduino.ORDER_ATOMIC) || '1000';
  /*if(text.length>16||text2.length>16){
      alert("string is too long");
  }*/
  Blockly.Arduino.definitions_['define_wire'] = '#include <Wire.h>\n';
  Blockly.Arduino.definitions_['define_softwareserial'] = '#include <SoftwareSerial.h>\n';
  Blockly.Arduino.definitions_['define_rgb_h'] = '#include "rgb_lcd.h"\n';
  Blockly.Arduino.definitions_['define_rgb_var'] = 'rgb_lcd rgbLcd;\n';
     
  Blockly.Arduino.setups_['setup_lcd'] = 'rgbLcd.begin(16,2);\n';
  var code;
  code    = 'rgbLcd.setCursor(0,0);\n';
  code    += 'rgbLcd.print('+text+');\n';//text.replace(new RegExp('\'',"gm"),'')
  code    += 'rgbLcd.setCursor(0,1);\n';
  code    += 'rgbLcd.print('+text2+');\n';
  code    += 'delay('+delay_time+');\n';
  return code;
};

Blockly.Arduino.grove_serial_lcd_power = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var dropdown_stat = this.getFieldValue('STAT');

  Blockly.Arduino.definitions_['define_seriallcd'] = '#include <SerialLCD.h>\n';
  Blockly.Arduino.definitions_['define_softwareserial'] = '#include <SoftwareSerial.h>\n';
  //generate PIN#+1 port
  var NextPIN = _get_next_pin(dropdown_pin);

  Blockly.Arduino.definitions_['var_lcd'+dropdown_pin] = 'SerialLCD slcd_'+dropdown_pin+'('+dropdown_pin+','+NextPIN+');\n';
  var code = 'slcd_'+dropdown_pin;
  if(dropdown_stat==="ON"){
    code += '.Power();\n';
  } else {
    code += '.noPower();\n';
  }
  return code;
};



Blockly.Arduino.grove_serial_lcd_effect = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var dropdown_stat = this.getFieldValue('STAT');

  Blockly.Arduino.definitions_['define_seriallcd'] = '#include <SerialLCD.h>\n';
  Blockly.Arduino.definitions_['define_softwareserial'] = '#include <SoftwareSerial.h>\n';
  //generate PIN#+1 port
  var NextPIN = _get_next_pin(dropdown_pin);

  Blockly.Arduino.definitions_['var_lcd'+dropdown_pin] = 'SerialLCD slcd_'+dropdown_pin+'('+dropdown_pin+','+NextPIN+');\n';
  var code = 'slcd_'+dropdown_pin;
  if(dropdown_stat==="LEFT"){
    code += '.scrollDisplayLeft();\n';
  } else if(dropdown_stat==="RIGHT"){
    code += '.scrollDisplayRight();\n';
  } else {
    code += '.autoscroll();\n';
  }
  return code;
};

Blockly.Arduino.grove_sound_sensor = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var code = 'analogRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.grove_pir_motion_sensor = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  var code = 'digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.grove_line_finder = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  var code = 'digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.grove_ultrasonic_ranger = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var dropdown_unit = this.getFieldValue('UNIT');
  Blockly.Arduino.definitions_['define_ultrasonic'] = '#include <Ultrasonic.h>\n';
  Blockly.Arduino.definitions_['var_ultrasonic'+dropdown_pin] = 'Ultrasonic ultrasonic_'+dropdown_pin+'('+dropdown_pin+');';
  var code;
  if(dropdown_unit==="cm"){
    code = 'ultrasonic_'+dropdown_pin+'.MeasureInCentimeters()';
  } else {
    code = 'ultrasonic_'+dropdown_pin+'.MeasureInInches()';
  }
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.grove_motor_shield = function() {
  var dropdown_direction = this.getFieldValue('DIRECTION');
  var speed = 127;//Blockly.Arduino.valueToCode(this, 'SPEED', Blockly.Arduino.ORDER_ATOMIC) || '127';
  Blockly.Arduino.setups_["setup_motor"] = "pinMode(8,OUTPUT);//I1\n"+
  "  pinMode(11,OUTPUT);//I2\n"+
  "  pinMode(9,OUTPUT);//speedPinA\n"+
  "  pinMode(12,OUTPUT);//I3\n"+
  "  pinMode(13,OUTPUT);//i4\n"+
  "  pinMode(10,OUTPUT);//speedPinB\n";
  var code = "";
  if(dropdown_direction==="forward"){
    Blockly.Arduino.definitions_['define_forward'] = "void forward()\n"+
"{\n"+
     "  analogWrite(9,"+speed+");//input a simulation value to set the speed\n"+
     "  analogWrite(10,"+speed+");\n"+
     "  digitalWrite(13,HIGH);//turn DC Motor B move clockwise\n"+
     "  digitalWrite(12,LOW);\n"+
     "  digitalWrite(11,LOW);//turn DC Motor A move anticlockwise\n"+
     "  digitalWrite(8,HIGH);\n"+
"}\n";
    code="forward();\n";
  } else if (dropdown_direction==="right") {
    Blockly.Arduino.definitions_['define_right'] = "void right()\n"+
"{\n"+
     "  analogWrite(9,"+speed+");//input a simulation value to set the speed\n"+
     "  analogWrite(10,"+speed+");\n"+
     "  digitalWrite(13,LOW);//turn DC Motor B move anticlockwise\n"+
     "  digitalWrite(12,HIGH);\n"+
     "  digitalWrite(11,LOW);//turn DC Motor A move anticlockwise\n"+
     "  digitalWrite(8,HIGH);\n"+
"}\n\n";
    code="right();\n";
  } else if (dropdown_direction==="left") {
    Blockly.Arduino.definitions_['define_left'] = "void left()\n"+
"{\n"+
     "  analogWrite(9,"+speed+");//input a simulation value to set the speed\n"+
     "  analogWrite(10,"+speed+");\n"+
     "  digitalWrite(13,HIGH);//turn DC Motor B move clockwise\n"+
     "  digitalWrite(12,LOW);\n"+
     "  digitalWrite(11,HIGH);//turn DC Motor A move clockwise\n"+
     "  digitalWrite(8,LOW);\n"+
"}\n\n";
    code="left();\n";
  } else if (dropdown_direction==="backward"){
    Blockly.Arduino.definitions_['define_backward'] = "void backward()\n"+
"{\n"+
     "  analogWrite(9,"+speed+");//input a simulation value to set the speed\n"+
     "  analogWrite(10,"+speed+");\n"+
     "  digitalWrite(13,LOW);//turn DC Motor B move anticlockwise\n"+
     "  digitalWrite(12,HIGH);\n"+
     "  digitalWrite(11,HIGH);//turn DC Motor A move clockwise\n"+
     "  digitalWrite(8,LOW);\n"+
"}\n\n";
    code="backward();\n";
  } else if (dropdown_direction==="stop"){
    Blockly.Arduino.definitions_['define_stop'] = "void stop()\n"+
"{\n"+
     "digitalWrite(9,LOW);// Unenble the pin, to stop the motor. this should be done to avid damaging the motor.\n"+
     "digitalWrite(10,LOW);\n"+
     "delay(1000);\n"+
"}\n\n"
    code="stop();\n";
  }
  return code;
};

Blockly.Arduino.grove_thumb_joystick =  function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var dropdown_axis = this.getFieldValue('AXIS');
  var stickPIN = "0"
  if(dropdown_axis==="y"){
    stickPIN = _get_next_pin(dropdown_pin);
  } else {
    stickPIN = dropdown_pin
  }
  var code = 'analogRead('+stickPIN+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

function hexToR(h) {return parseInt((cutHex(h)).substring(0,2),16)}
function hexToG(h) {return parseInt((cutHex(h)).substring(2,4),16)}
function hexToB(h) {return parseInt((cutHex(h)).substring(4,6),16)}
function cutHex(h) {return (h.charAt(0)=="#") ? h.substring(1,7):h}

Blockly.Arduino.grove_rgb_led = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var NextPIN = _get_next_pin(dropdown_pin);

  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', OUTPUT);';
  Blockly.Arduino.setups_['setup_input_'+NextPIN] = 'pinMode('+NextPIN+', OUTPUT);';
  Blockly.Arduino.definitions_['define_uint8'] = "#define uint8 unsigned char";
  Blockly.Arduino.definitions_['define_uint16'] = "#define uint16 unsigned int";
  Blockly.Arduino.definitions_['define_uint32'] = "#define uint32 unsigned long int";
  Blockly.Arduino.definitions_['define_clkproduce_'+dropdown_pin] = "void ClkProduce_"+dropdown_pin+"(void)\n"+
  "{\n"+
  "  digitalWrite("+dropdown_pin+", LOW);\n"+
  "  delayMicroseconds(20);\n"+
  "  digitalWrite("+dropdown_pin+", HIGH);\n"+
  "  delayMicroseconds(20);\n"+
  "}\n";
  Blockly.Arduino.definitions_['define_send32zero_'+dropdown_pin] = "void Send32Zero_"+dropdown_pin+"(void)\n"+
  "{\n"+
  "  uint8 i;\n"+
  "  for (i=0; i<32; i++)\n"+
  "  {\n"+
  "    digitalWrite("+NextPIN+", LOW);\n"+
  "    ClkProduce_"+dropdown_pin+"();\n"+
  "  }\n"+
  "}\n";
  Blockly.Arduino.definitions_['define_taskanticode'] = "uint8 TakeAntiCode(uint8 dat)\n"+
  "{\n"+
  "  uint8 tmp = 0;\n"+
  "  if ((dat & 0x80) == 0)\n"+
  "  {\n"+
  "    tmp |= 0x02;\n"+
  "  }\n"+
  "  \n"+
  "  if ((dat & 0x40) == 0)\n"+
  "  {\n"+
  "    tmp |= 0x01;\n"+
  "  }\n"+
  "  return tmp;\n"+
  "}\n";
  Blockly.Arduino.definitions_['define_datasend_'+dropdown_pin] = "// gray data\n"+
  "void DatSend_"+dropdown_pin+"(uint32 dx)\n"+
  "{\n"+
  "  uint8 i;\n"+
  "  for (i=0; i<32; i++)\n"+
  "  {\n"+
  "    if ((dx & 0x80000000) != 0)\n"+
  "    {\n"+
  "      digitalWrite("+NextPIN+", HIGH);\n"+
  "    }\n"+
  "    else\n"+
  "    {\n"+
  "      digitalWrite("+NextPIN+", LOW);\n"+
  "    }\n"+
  "  dx <<= 1;\n"+
  "  ClkProduce_"+dropdown_pin+"();\n"+
  "  }\n"+
  "}\n";
  Blockly.Arduino.definitions_['define_datadealwithsend_'+dropdown_pin] = "// data processing\n"+
"void DataDealWithAndSend_"+dropdown_pin+"(uint8 r, uint8 g, uint8 b)\n"+
"{\n"+
  "  uint32 dx = 0;\n"+
  "  dx |= (uint32)0x03 << 30;             // highest two bits 1，flag bits\n"+
  "  dx |= (uint32)TakeAntiCode(b) << 28;\n"+
  "  dx |= (uint32)TakeAntiCode(g) << 26;\n"+
  "  dx |= (uint32)TakeAntiCode(r) << 24;\n"+
 "\n"+
  "  dx |= (uint32)b << 16;\n"+
  "  dx |= (uint32)g << 8;\n"+
  "  dx |= r;\n"+
 "\n"+
  "  DatSend_"+dropdown_pin+"(dx);\n"+
"}\n";
  var code = "Send32Zero_"+dropdown_pin+"(); // begin\n";
  //console.log(this.itemCount_);
  if (this.itemCount_ == 0) {
    return '';
  } else {
    for (var n = 0; n < this.itemCount_; n++) {
      var colour_rgb = this.getFieldValue('RGB'+n);
      //console.log(colour_rgb);
      code += "DataDealWithAndSend_"+dropdown_pin+"("+hexToR(colour_rgb)+", "+hexToG(colour_rgb)+", "+hexToB(colour_rgb)+"); // first node data\n";
    }
  }
  code += "Send32Zero_"+dropdown_pin+"();  // send to update data\n";
  return code;
};

Blockly.Arduino.grove_bluetooth_slave = function() {
  var dropdown_pin = this.getFieldValue('PIN');
  var NextPIN = _get_next_pin(dropdown_pin);
  var name = this.getFieldValue('NAME')
  var pincode = this.getFieldValue('PINCODE');
  var statement_receive = Blockly.Arduino.statementToCode(this, "RCV")
  var statement_send = Blockly.Arduino.statementToCode(this, "SNT")
  /* if(pincode.length != 4){
    alert("pincode length should be 4");
  } */
  Blockly.Arduino.definitions_['define_softwareserial'] = '#include <SoftwareSerial.h>\n';
  Blockly.Arduino.definitions_['var_bluetooth_'+dropdown_pin] = 'SoftwareSerial blueToothSerial_'+dropdown_pin+'('+dropdown_pin+','+NextPIN+');\n';

  Blockly.Arduino.setups_['setup_bluetooth_'+dropdown_pin] = 'Serial.begin(9600);\n';
  Blockly.Arduino.setups_['setup_bluetooth_'+dropdown_pin] += '  pinMode('+dropdown_pin+', INPUT);\n';
  Blockly.Arduino.setups_['setup_bluetooth_'+dropdown_pin] += '  pinMode('+NextPIN+', OUTPUT);\n';
  Blockly.Arduino.setups_['setup_bluetooth_'+dropdown_pin] += '  setupBlueToothConnection_'+dropdown_pin+'();\n';

  Blockly.Arduino.definitions_['define_setupBlueToothConnection_'+dropdown_pin] = 'void setupBlueToothConnection_'+dropdown_pin+'()\n'+
  '{\n'+
  '  blueToothSerial_'+dropdown_pin+'.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400\n'+
  '  blueToothSerial_'+dropdown_pin+'.print("\\r\\n+STWMOD=0\\r\\n"); //set the bluetooth work in slave mode\n'+
  '  blueToothSerial_'+dropdown_pin+'.print("\\r\\n+STNA='+name+'\\r\\n"); //set the bluetooth name as "'+name+'"\n'+
  '  blueToothSerial_'+dropdown_pin+'.print("\\r\\n+STPIN=0000\\r\\n");//Set SLAVE pincode"0000"\n'+
  '  blueToothSerial_'+dropdown_pin+'.print("\\r\\n+STOAUT=1\\r\\n"); // Permit Paired device to connect me\n'+
  '  blueToothSerial_'+dropdown_pin+'.print("\\r\\n+STAUTO=0\\r\\n"); // Auto-connection should be forbidden here\n'+
  '  delay(2000); // This delay is required.\n'+
  '  blueToothSerial_'+dropdown_pin+'.print("\\r\\n+INQ=1\\r\\n"); //make the slave bluetooth inquirable \n'+
  '  Serial.println("The slave bluetooth is inquirable!");\n'+
  '  delay(2000); // This delay is required.\n'+
  '  blueToothSerial_'+dropdown_pin+'.flush();\n'+
  '}\n';
  var code = 'char recvChar_'+dropdown_pin+';\n'+
  'while(1) {\n'+
  '  if(blueToothSerial_'+dropdown_pin+'.available()) {//check if there is any data sent from the remote bluetooth shield\n'+
  '    recvChar_'+dropdown_pin+' = blueToothSerial_'+dropdown_pin+'.read();\n'+
  '    Serial.print(recvChar_'+dropdown_pin+');\n'+
       statement_receive+
  '  }\n'+
  '  if(Serial.available()){//check if there is any data sent from the local serial terminal, you can add the other applications here\n'+
  '    recvChar_'+dropdown_pin+' = Serial.read();\n'+
  '    blueToothSerial_'+dropdown_pin+'.print(recvChar_'+dropdown_pin+');\n'+
       statement_send+
  '  }\n'+
  '}\n';
  return code;
};