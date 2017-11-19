/**
 * @license
 * Visual Blocks Language
 *
 * Copyright 2012 Google Inc.
 * https://blockly.googlecode.com/
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
 * @fileoverview Generating OpenSCAD for logic blocks.
 * @author q.neutron@gmail.com (Quynh Neutron)
 */
'use strict';

goog.provide('Blockly.OpenSCAD.logic');

goog.require('Blockly.OpenSCAD');


Blockly.OpenSCAD['controls_if'] = function(block) {
  // If/elseif/else condition.
  var n = 0;
  var argument = Blockly.OpenSCAD.valueToCode(block, 'IF' + n,
      Blockly.OpenSCAD.ORDER_NONE) || 'false';
  var branch = Blockly.OpenSCAD.statementToCode(block, 'DO' + n);

  var hiya = Blockly.OpenSCAD.returnIfVarCode(block);
  var aC = hiya[0];
  var aP = hiya[1];


  var code = 'if (' + argument + ') {\n' +aC[0] + branch + '\n'  + aP[0] + '}';
  for (n = 1; n <= block.elseifCount_; n++) {
    argument = Blockly.OpenSCAD.valueToCode(block, 'IF' + n,
        Blockly.OpenSCAD.ORDER_NONE) || 'false';
    branch = Blockly.OpenSCAD.statementToCode(block, 'DO' + n);
    code += ' else if (' + argument + ') {\n' + aC[n] + branch + '\n' + aP[n] + '}';
  }
  if (block.elseCount_) {
    branch = Blockly.OpenSCAD.statementToCode(block, 'ELSE');
    code += ' else {\n' + aC[aC.length - 1] +  branch + '\n' + aP[aP.length - 1] + '}';
  }
  return code + '\n';
};

Blockly.OpenSCAD['logic_compare'] = function(block) {
  // Comparison operator.
  var OPERATORS = {
    EQ: '==',
    NEQ: '!=',
    LT: '<',
    LTE: '<=',
    GT: '>',
    GTE: '>='
  };
  var operator = OPERATORS[block.getFieldValue('OP')];
  var order = (operator == '==' || operator == '!=') ?
      Blockly.OpenSCAD.ORDER_EQUALITY : Blockly.OpenSCAD.ORDER_RELATIONAL;
  var argument0 = Blockly.OpenSCAD.valueToCode(block, 'A', order) || '0';
  var argument1 = Blockly.OpenSCAD.valueToCode(block, 'B', order) || '0';
  var code = argument0 + ' ' + operator + ' ' + argument1;
  if (block.getParent())
    return [code, order];
  else return ['//' + code, order];
};

Blockly.OpenSCAD['logic_operation'] = function(block) {
  // Operations 'and', 'or'.
  var operator = (block.getFieldValue('OP') == 'AND') ? '&&' : '||';
  var order = (operator == '&&') ? Blockly.OpenSCAD.ORDER_LOGICAL_AND :
      Blockly.OpenSCAD.ORDER_LOGICAL_OR;
  var argument0 = Blockly.OpenSCAD.valueToCode(block, 'A', order);
  var argument1 = Blockly.OpenSCAD.valueToCode(block, 'B', order);
  if (!argument0 && !argument1) {
    // If there are no arguments, then the return value is false.
    argument0 = 'false';
    argument1 = 'false';
  } else {
    // Single missing arguments have no effect on the return value.
    var defaultArgument = (operator == '&&') ? 'true' : 'false';
    if (!argument0) {
      argument0 = defaultArgument;
    }
    if (!argument1) {
      argument1 = defaultArgument;
    }
  }
  var code = argument0 + ' ' + operator + ' ' + argument1;
  if (block.getParent())
    return [code, order];
  else return ['//' + code, order];
};

Blockly.OpenSCAD['logic_negate'] = function(block) {
  // Negation.
  var order = Blockly.OpenSCAD.ORDER_LOGICAL_NOT;
  var argument0 = Blockly.OpenSCAD.valueToCode(block, 'BOOL', order) ||
      'true';
  var code = '!' + argument0;
  if (block.getParent())
    return [code, order];
  else return ['//' + code, order];
};

Blockly.OpenSCAD['logic_boolean'] = function(block) {
  // Boolean values true and false.
  var code = (block.getFieldValue('BOOL') == 'TRUE') ? 'true' : 'false';
  if (block.getParent())
    return [code, Blockly.OpenSCAD.ORDER_ATOMIC];
  else return ['//' + code, Blockly.OpenSCAD.ORDER_ATOMIC];
};

Blockly.OpenSCAD['logic_null'] = function(block) {
  // Null data type.
  var code = 'null';
  if (block.getParent())
    return [code, Blockly.OpenSCAD.ORDER_ATOMIC];
  else return ['//' + code, Blockly.OpenSCAD.ORDER_ATOMIC];
};

Blockly.OpenSCAD['logic_ternary'] = function(block) {
  // Ternary operator.
  var value_if = Blockly.OpenSCAD.valueToCode(block, 'IF',
      Blockly.OpenSCAD.ORDER_CONDITIONAL) || 'false';
  var value_then = Blockly.OpenSCAD.valueToCode(block, 'THEN',
      Blockly.OpenSCAD.ORDER_CONDITIONAL) || 'null';
  var value_else = Blockly.OpenSCAD.valueToCode(block, 'ELSE',
      Blockly.OpenSCAD.ORDER_CONDITIONAL) || 'null';
  var code = value_if + ' ? ' + value_then + ' : ' + value_else
  if (block.getParent())
    return [code, Blockly.OpenSCAD.ORDER_CONDITIONAL];
  else return ['//' + code, Blockly.OpenSCAD.ORDER_CONDITIONAL];
};

