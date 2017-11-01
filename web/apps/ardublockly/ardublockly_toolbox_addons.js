/**
 * @license Licensed under the Apache License, Version 2.0 (the "License"):
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 * @fileoverview XML toolbox embedded into a JavaScript text string.
 */
'use strict';

/** Create a namespace for the application. */
var Ardublockly = Ardublockly || {};

Ardublockly.TOOLBOX_ADDITIONAL_XML =
'  <sep></sep>' +
'  <category id="catGrove" name="Grove">' +
'    <block type="grove_led"></block>' +
'    <block type="grove_relay"></block>' +
'    <block type="grove_dht11"></block>' +
'    <block type="grove_serial_lcd_iic"></block>' +
'  </category>';

Ardublockly.TOOLBOX_XML = Ardublockly.TOOLBOX_BEGIN_XML + Ardublockly.TOOLBOX_CORE_XML +  Ardublockly.TOOLBOX_ADDITIONAL_XML + Ardublockly.TOOLBOX_END_XML;
