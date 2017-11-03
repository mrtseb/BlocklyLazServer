//http://www.seeedstudio.com/wiki/GROVE_System
//http://www.seeedstudio.com/depot/index.php?main_page=advanced_search_result&search_in_description=1&keyword=grovefamily
//support starter bundle example http://www.seeedstudio.com/wiki/GROVE_-_Starter_Kit_V1.1b

/**
 * @license
 * Visual Blocks Editor
 *
 * Copyright 2012 Fred Lin.
 * https://github.com/gasolin/BlocklyDuino
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
 * @fileoverview Helper functions for generating seeeduino grove blocks.
 * @author gasolin@gmail.com (Fred Lin)
 */
'use strict';

goog.provide('Blockly.Blocks.mbot');

goog.require('Blockly.Blocks');
goog.require('Blockly.Types');

Blockly.Blocks.mbot_id ='';

Blockly.Blocks['mbot_light'] = {
  
 
  init: function() {
    this.setColour(50);
    this.appendDummyInput()
        
        //.appendField(new Blockly.FieldImage("../../media/devices/mbot.png", 64, 64))
		.appendField("Luminosité sur")
        .appendField(new Blockly.FieldDropdown([["la carte", "6"], ["le port 3", "3"],  ["le port 4", "4"]]), "PORT");
	this.setOutput(true, 'Boolean');
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['mbot_ultrasonic'] = {
  
 
  init: function() {
    this.setColour(50);
    this.appendDummyInput()        
        //.appendField(new Blockly.FieldImage("../../media/devices/mbot.png", 64, 64))
		.appendField("Distance de l'obstacle en cm mesurée sur")
        .appendField(new Blockly.FieldDropdown([["PORT1", "1"],["PORT2", "2"],["PORT3", "3"],["PORT4", "4"]]), "PORT");
	this.setOutput(true, 'Boolean');
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['mbot_follower'] = {
  
 
  init: function() {
    this.setColour(50);
    this.appendDummyInput()        
        //.appendField(new Blockly.FieldImage("../../media/devices/mbot.png", 64, 64))
		.appendField("Suiveur de ligne")
        .appendField(new Blockly.FieldDropdown([["Port1", "1"],["Port2", "2"],["Port3", "3"],["Port4", "4"]]), "PORT")
		.appendField(new Blockly.FieldDropdown([["Côté gauche", "2"],["Côté droite", "1"]]), "COTE")
		.appendField("est")
		.appendField(new Blockly.FieldDropdown([["Noir", "0"],["Blanc", "1"]]), "COULEUR")
		;
	this.setOutput(true, 'Boolean');
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['mbot_core_button'] = {
  
 
  init: function() {
    this.setColour(50);
    this.appendDummyInput()
        
        //.appendField(new Blockly.FieldImage("../../media/devices/mbot.png", 64, 64))
		.appendField("Bouton de la carte")
        .appendField(new Blockly.FieldDropdown([["enfonçé", "0"],["relâché", "1"]]), "BOUTON");
	this.setOutput(true, 'Boolean');
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['mbot_ir_loop'] = {
  
 
  init: function() {
    this.setColour(50);
    this.appendDummyInput()        
        .appendField("Boucle de la télécommande");
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setInputsInline(true); 
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['mbot_ir_rec'] = {
  
 
  init: function() {
    this.setColour(50);
    this.appendDummyInput()        
        //.appendField(new Blockly.FieldImage("../../media/devices/mbot.png", 64, 64))
		.appendField("Touche de la télécommande")
        .appendField(new Blockly.FieldDropdown([
		["A", "69"],["B", "70"],["C", "71"],["D", "68"],["E", "67"],["F", "13"],
		["▲", "64"],["▼", "25"],["◄", "7"],["►", "9"],["Réglage", "21"],
		["R0", "22"],["R1", "12"],["R2", "24"],["R3", "94"],["R4", "8"],["R5", "28"],
		["R6", "90"],["R8", "66"],["R9", "82"],["R10", "74"]
		]), "TOUCHE");
	this.setOutput(true, 'Boolean');
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['mbot_init'] = {
  init: function() {
	
    this.appendDummyInput()
	    .appendField(new Blockly.FieldImage("../../media/devices/mbot.png", 64, 64))
        .appendField("Initialisation Mbot");
	//this.appendValueInput("TEXT", 'String');
        
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
  }
 };
Blockly.Blocks._change = function(event) {
	
    if (!Blockly.Blocks.un_bloc.workspace || event.type == Blockly.Events.MOVE ||
        event.type == Blockly.Events.UI) {
        return;  // Block deleted or irrelevant event
    }
    //alert(Blockly.Blocks.mbot_id);
    if (Blockly.Blocks.mbot_id != 'MBOT-ID') {
      Blockly.Blocks.un_bloc.setWarningText('Il faut ajouter un bloc de configuration Mbot','mbot_init');
    } else {
      Blockly.Blocks.un_bloc.setWarningText(null, 'mbot_init');
    }
  }

Blockly.Blocks['mbot_move'] = {
  init: function() {
    this.appendDummyInput()
	    //.appendField(new Blockly.FieldImage("../../media/devices/mbot_motor.jpg", 64, 64))
        .appendField(new Blockly.FieldDropdown([["avancer","1"], ["reculer","2"],["tourner à droite","4"], ["tourner à gauche","3"]]), "COMMANDE")
        .appendField("Puissance")
        .appendField(new Blockly.FieldDropdown([["255","255"], ["100","100"], ["50","50"], ["0","0"], ["-50","-50"], ["-100","-100"], ["-255","-255"]]), "VITESSE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
 Blockly.Blocks.un_bloc=this;
 
  },
  onchange: function(event) {
	  Blockly.Blocks._change(event);
  }
};

Blockly.Blocks['mbot_conf_motor'] = {
  init: function() {
    this.appendDummyInput()
	    //.appendField(new Blockly.FieldImage("../../media/devices/mbot_motor.jpg", 64, 64))
        .appendField("Moteur")
		.appendField(new Blockly.FieldDropdown([["M1","M1"], ["M2","M2"]]), "MOTEUR")
        .appendField("à la vitesse")
        .appendField(new Blockly.FieldDropdown([["255","255"], ["100","100"], ["50","50"], ["0","0"], ["-50","-50"], ["-100","-100"], ["-255","-255"]]), "POWER");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
 Blockly.Blocks.un_bloc=this;
  },
  onchange: function(event) {
	  Blockly.Blocks._change(event);
  }
};

Blockly.Blocks['mbot_buzzer'] = {
	init: function() {
    this.appendDummyInput()
	    //.appendField(new Blockly.FieldImage("../../media/devices/mbot_motor.jpg", 64, 64))
        .appendField("Jouer la note")
		.appendField(new Blockly.FieldDropdown([
		["C2","65"],
		["D2","2"],
		["E2","65"],
		["F2","65"],
		["G2","2"],
		["A2","65"],
		["B2","2"],
		["C3","131"],
		["D3","2"],
		["E3","65"],
		["F3","65"],
		["G3","2"],
		["A3","65"],
		["B3","2"],
		["C4","65"],
		["D4","2"],
		["E4","65"],
		["F4","65"],
		["G4","2"],
		["A4","65"],
		["B4","2"],
		["C5","65"],
		["D5","2"],
		["E5","65"],
		["F5","65"],
		["G5","2"],
		["A5","65"],
		["B5","2"],
		["C6","65"],
		["D6","2"],
		["E6","65"],
		["F6","65"],
		["G6","2"],
		["A6","65"],
		["B6","2"],
		["C7","65"],
		["D7","2"],
		["E7","65"],
		["F7","65"],
		["G7","2"],
		["A7","65"],
		["B7","2"],
		["C8","65"],
		["D8","2"]		
		]), "NOTE")
        .appendField(new Blockly.FieldDropdown([["1/2","500"], ["1/4","250"], ["1/8","125"], ["1","1000"], ["2","2000"]]), "TEMPS")
		.appendField("temps")
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
    this.setTooltip("");
    this.setHelpUrl("");
    Blockly.Blocks.un_bloc=this;
  },
  onchange: function(event) {
	  Blockly.Blocks._change(event);
  }
}

Blockly.Blocks['mbot_leds'] = {
  init: function() {
    this.appendDummyInput()
	    //.appendField(new Blockly.FieldImage("../../media/devices/mbot_mcore_leds.jpg", 64, 64))
        .appendField("LED")
		.appendField(new Blockly.FieldDropdown([["Tout","0"], ["Led de gauche","2"], ["Led de droite","1"]]), "LED")
        .appendField("en rouge")
        .appendField(new Blockly.FieldDropdown([["0","0"], ["20","20"], ["60","60"], ["150","150"], ["255","255"]]), "ROUGE")
		.appendField("en vert")
        .appendField(new Blockly.FieldDropdown([["0","0"], ["20","20"], ["60","60"], ["150","150"], ["255","255"]]), "VERT")
		.appendField("en bleu")
        .appendField(new Blockly.FieldDropdown([["0","0"], ["20","20"], ["60","60"], ["150","150"], ["255","255"]]), "BLEU");
		
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
 Blockly.Blocks.un_bloc=this;
  },
  onchange: function(event) {
	  Blockly.Blocks._change(event);
  }
};
