'use strict';

goog.provide('Blockly.MutatorPlus');

goog.require('Blockly.Mutator');
goog.require('Blockly.Bubble');
goog.require('Blockly.Icon');
goog.require('goog.Timer');
goog.require('goog.dom');

Blockly.MutatorPlus = function(quarkNames) {
    Blockly.MutatorPlus.superClass_.constructor.call(this, this, null);
};
goog.inherits(Blockly.MutatorPlus, Blockly.Mutator, Blockly.Icon);

Blockly.MutatorPlus.prototype.clicked_ = false;

/**
 * Icon in base64 format.
 * @private
 */
//Blockly.Mutator.prototype.png_ = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABEAAAARCAYAAAA7bUf6AAAABGdBTUEAALGPC/xhBQAAAAlwSFlzAAANyAAADcgBffIlqAAAAAd0SU1FB98DGhULOIajyb8AAAHMSURBVDjLnZS9SiRBFIXP/CQ9iIHgPoGBTo8vIAaivoKaKJr6DLuxYqKYKIqRgSCMrblmIxqsICgOmAriziIiRXWjYPdnUDvT2+PMsOyBoop7qk71vedWS5KAkrWsGUMjSYjpgSQhNoZGFLEKeGoKGMNttUpULkOhAFL3USiA70MQEBnDDeDJWtaqVaJeB7uNICAKQ1ZkDI1yufOm+XnY2YHl5c6874MxPClJiDulkMvBxYWrw/095POdU0sS4hxALqcWtreloSGpVJLGxtL49bX0+Ci9vUkzM2kcXGFbypUKxHHLBXZ3YW4ONjfh4yN1aGIiPQOQEenrg6MjR+zvZz99Y8PFT09hYCArktdfsFY6PHTr83NlUKu5+eREennJchmR/n5pYcGtJyezG6em3Dw7Kw0OZrlMOr6f1gTg4ACWlmBvz9WoifHxbDpf3Flfd+54njQ9ncYvL6WHB+n9XVpcbHOnW59IUKu5m+p11zftfLHo+qRorZ6Hh/Xt7k5fsLUl1evS1dWfG9swMiJZq9+KIlaD4P/eztkZNgz5LsAzhpvjY6JK5d9e8eioE3h95SdQbDrkhSErxvArjkl6/U/imMQYnsKQH02BT7vbZZfVOiWhAAAAAElFTkSuQmCC';

/**
 * Create the icon on the block.
 */
Blockly.MutatorPlus.prototype.createIcon = function() {
  if (this.iconMark_) {
    // Icon already exists.
    return;
  }
  Blockly.Icon.prototype.createIconOld.call(this);
  Blockly.Icon.radius = 8;
  /* Here's the markup that will be generated:
  <rect class="blocklyIconShield" width="16" height="16" rx="4" ry="4"/>
  <text class="blocklyIconMark" x="8" y="12">+</text>
  */
  var quantum = Blockly.Icon.radius / 2;
  var iconShield = Blockly.createSvgElement('rect',
      {'class': 'blocklyIconShield',
       'width': 4 * quantum,
       'height': 4 * quantum,
       'rx': quantum,
       'ry': quantum}, this.iconGroup_);
  this.iconMark_ = Blockly.createSvgElement('text',
      {'class': 'blocklyIconMark',
       'x': Blockly.Icon.radius,
       'y': 2 * Blockly.Icon.radius - 4}, this.iconGroup_);
  this.iconMark_.appendChild(document.createTextNode('\u002b'));
};

Blockly.MutatorPlus.prototype.iconClick_ = function(e) {
  if (Blockly.dragMode_ == 2) {
    // Drag operation is concluding.  Don't activate the mutator.
    return;
  }
  if (this.block_.isEditable()) {
      this.block_.updateShape_(1);
  }
  goog.Timer.callOnce(
    this.block_.bumpNeighbours_, Blockly.BUMP_DELAY, this.block_);
};