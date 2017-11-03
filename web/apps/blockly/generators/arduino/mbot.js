/**
 * @license Licensed under the Apache License, Version 2.0 (the "License"):
 *          http://www.apache.org/licenses/LICENSE-2.0
 */

/**
 * @fileoverview Code generator for Arduino Digital and Analogue input/output.
 *     Arduino built in function docs: http://arduino.cc/en/Reference/HomePage
 */
'use strict';

goog.provide('Blockly.Arduino.mbot');

goog.require('Blockly.Arduino');


Blockly.Arduino.mbot_init = function(block) {
	
  
  Blockly.Arduino.definitions_['define_wire'] = '#include <Wire.h>\n';
  Blockly.Arduino.definitions_['define_softwareserial'] = '#include <SoftwareSerial.h>\n';
  Blockly.Arduino.definitions_['define_memcore_h'] = '#include <MeMCore.h>\n';
  Blockly.Arduino.definitions_['define_memcore_object9'] = 'MeDCMotor motor_9(9);\n';
  Blockly.Arduino.definitions_['define_memcore_object10'] = 'MeDCMotor motor_10(10);\n';
  
  Blockly.Arduino.definitions_['define_delay_function'] =
  'void _delay(float seconds){\n' +
  '  long endTime = millis() + seconds * 1000;\n' +
  '  while(millis() < endTime)_loop();\n' +
  '}\n';

  Blockly.Arduino.definitions_['define_loop_function'] =  
  'void _loop(){\n' +
  '}\n';
  
  Blockly.Arduino.definitions_['define_move_function'] = 
  'void move(int direction, int speed)\n' +
  '{\n'  +
  '    int leftSpeed = 0;\n' +
  '    int rightSpeed = 0;\n' +
  '    if(direction == 1){\n' +
  '      	leftSpeed = speed;\n' +
  '      	rightSpeed = speed;\n' +
  '    }else if(direction == 2){\n' +
  '      	leftSpeed = -speed;\n' +
  '      	rightSpeed = -speed;\n' +
  '    }else if(direction == 3){\n' +
  '      	leftSpeed = -speed;\n' +
  '      	rightSpeed = speed;\n' +
  '    }else if(direction == 4){\n' +
  '      	leftSpeed = speed;\n' +
  '      	rightSpeed = -speed;\n' +
  '    }\n' +
  '    motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));\n' +
  '    motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));\n' +
  '}\n';
  
  
  return "_loop();\n";
}


Blockly.Arduino.mbot_conf_motor = function(block) {
	
  var moteur = block.getFieldValue('MOTEUR');
  var power = block.getFieldValue('POWER');	
  var code;
  if (moteur=='M1') {
    code = 'motor_9.run((9)==M1?-('+power+'):('+power+'));\n';  
  } else {
	code = 'motor_10.run((10)==M1?-('+power+'):('+power+'));\n';    
}
  return code;
  
  
}

Blockly.Arduino.mbot_move = function(block) {
	
  var commande = block.getFieldValue('COMMANDE');
  var vitesse = block.getFieldValue('VITESSE');	
  
  var code = 'move('+commande+','+vitesse+');\n';  
  
   return code;
}

Blockly.Arduino.mbot_leds = function(block) {
	
  var led = block.getFieldValue('LED');
  var rouge = block.getFieldValue('ROUGE');
  var vert = block.getFieldValue('VERT');
  var bleu = block.getFieldValue('BLEU');  
  Blockly.Arduino.definitions_['mbot_rgbled'] = 'MeRGBLed rgbled_7(7, 7==7?2:4);\n';
  var code= 'rgbled_7.setColor('+led+','+rouge+','+vert+','+bleu+');\n' +
  '  rgbled_7.show();\n';
  
   return code;
}

Blockly.Arduino.mbot_buzzer = function(block) {
  var note = block.getFieldValue('NOTE');
  var temps = block.getFieldValue('TEMPS');
  Blockly.Arduino.definitions_['mbot_light'] = 'MeBuzzer buzzer;\n';
  var code = 'buzzer.tone('+note+', '+temps+');\n' +
  '  delay(20);\n';
    
    return code;
  
 
}

Blockly.Arduino.mbot_light = function() {
  var port = this.getFieldValue('PORT');
  Blockly.Arduino.definitions_['mbot_light'] = 'MeLightSensor lightsensor_'+port+'('+port+');\n';
  var code;
  code = 'lightsensor_'+port+'.read()';
    
 return [code, Blockly.Arduino.ORDER_ATOMIC];
 
}