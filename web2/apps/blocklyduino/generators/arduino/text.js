/**
 * Visual Blocks Language
 *
 * Copyright 2012 Google Inc.
 * http://blockly.googlecode.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @fileoverview Generating Arduino for text blocks.
 * @author gasolin@gmail.com (Fred Lin)
 */
'use strict';

goog.provide('Blockly.Arduino.texts');

goog.require('Blockly.Arduino');

Blockly.Arduino.text = function() {
  // Text value.
  var code = Blockly.Arduino.quote_(this.getFieldValue('TEXT'));
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.text2 = function() {
  // Text value.
  
  var argument0 = Blockly.Arduino.valueToCode(this, 'TXT1',  Blockly.Arduino.ORDER_ATOMIC) || '';
  var argument1 = Blockly.Arduino.valueToCode(this, 'TXT2',  Blockly.Arduino.ORDER_ATOMIC) || '';
  var code = 'String('+argument0+')+String('+argument1+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

//Blockly.Arduino.text_print = = function() {
	//var code='';
	//return [code, Blockly.Arduino.ORDER_NONE];
//};
Blockly.Arduino.text_var2string= function() {
  // Text value.
  
  //var argument0 = Blockly.Arduino.valueToCode(this, 'TXT1',  Blockly.Arduino.ORDER_ATOMIC) || '0';
  //var argument1 = Blockly.Arduino.valueToCode(this, 'TXT2',  Blockly.Arduino.ORDER_ATOMIC) || '0';
  var code = "String('')+"+Blockly.Arduino.variableDB_.getName(this.getFieldValue('VAR'),Blockly.Variables.NAME_TYPE);
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};
Blockly.Arduino.text_append2 = function() {
  // Text value.
  
  //var argument0 = Blockly.Arduino.valueToCode(this, 'TXT1',  Blockly.Arduino.ORDER_ATOMIC) || '0';
  //var argument1 = Blockly.Arduino.valueToCode(this, 'TXT2',  Blockly.Arduino.ORDER_ATOMIC) || '0';
  var mavar = this.getFieldValue('VAR');
  var argument0 = Blockly.Arduino.valueToCode(this, 'TEXT',  Blockly.Arduino.ORDER_ATOMIC) || '\'\'';
  var code = 'String('+argument0+')+'+mavar;
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.text_append = function() {
  // Text value.
  
  //var argument0 = Blockly.Arduino.valueToCode(this, 'TXT1',  Blockly.Arduino.ORDER_ATOMIC) || '0';
  //var argument1 = Blockly.Arduino.valueToCode(this, 'TXT2',  Blockly.Arduino.ORDER_ATOMIC) || '0';
  var mavar = this.getFieldValue('VAR');
  var argument0 = Blockly.Arduino.valueToCode(this, 'TEXT',  Blockly.Arduino.ORDER_ATOMIC) || '\'\'';
  var code = mavar+'+String('+argument0+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


