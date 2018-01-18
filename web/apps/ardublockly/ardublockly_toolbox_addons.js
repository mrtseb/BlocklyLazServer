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
'    <block type="grove_tilt_switch"></block>' +
'    <block type="grove_relay"></block>' +
'    <block type="grove_dht11"></block>' +
'    <block type="grove_serial_lcd_iic"></block>' +
'    <block type="grove_ir_config"></block>' +
'    <block type="grove_ir_remote"></block>' +
'    <block type="grove_ultrasonic2"></block>' +
'  </category>' +
'  <sep></sep>' +
'  <sep></sep>' +
'  <category id="catMeteo" name="Meteo">' +
'    <block type="meteo_patm"></block>' +
'  </category>' +
'  <sep></sep>' +
'  <category id="catMbot" name="Mbot">' +
'    <block type="mbot_init"></block>' +
'    <block type="mbot_move"></block>' +
'    <block type="mbot_conf_motor"></block>' +
'    <block type="mbot_leds"></block>' +
'    <block type="mbot_buzzer"></block>' +
'    <block type="mbot_light"></block>' +
'   <block type="mbot_core_button"></block>' +
'   <block type="mbot_ir_rec"></block>' +
'   <block type="mbot_ir_loop"></block>' +
'   <block type="mbot_ultrasonic"></block>' +
'   <block type="mbot_follower"></block>' +
'  </category>' +
'  <sep></sep>' +
'  <category id="catRtc" name="Rtc">' +
'    <block type="grove_rtc_config"></block>' +
'    <block type="grove_rtc_get"></block>' +
'    <block type="grove_rtc2">' +
'      <value name="TIMES">' +
'        <block type="math_number">' +
'          <field name="NUM">1</field>' +
'        </block>' +
'      </value>' +
'    </block>' +
'  </category>';


Ardublockly.TOOLBOX_XML = Ardublockly.TOOLBOX_BEGIN_XML + Ardublockly.TOOLBOX_CORE_XML +  Ardublockly.TOOLBOX_ADDITIONAL_XML + Ardublockly.TOOLBOX_END_XML;
