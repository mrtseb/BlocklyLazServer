// geom_set_ops.js
// contains the definitions of the Geometric Set operations 
// union, difference, intersection, and hull
// These blocks are made with mutators that allow them to 
// be expanded by the user to take more than the default two
// object arguments.
// 
goog.require('Blockly.Blocks');
//goog.require('Blockly.MutatorPlus');

Blockly.Blocks['union'] = {
  init: function() {
    this.category = 'SET_OP';
    this.setHelpUrl('http://www.example.com/');
    this.setColour(Blockscad.Toolbox.HEX_SETOP);
    this.appendDummyInput()
        .appendField(Blockscad.Msg.UNION);
    this.appendStatementInput("A")
        .setCheck(["CSG","CAG"]);
    this.appendStatementInput("PLUS0")
        .appendField(Blockscad.Msg.PLUS)
        .setCheck(["CSG","CAG"]);
    this.setInputsInline(true);
    this.setPreviousStatement(true, ["CSG","CAG"]);
    this.setTooltip(Blockscad.Msg.UNION_TOOLTIP);
    // try to set up a mutator - Jennie
    this.setMutatorPlus(new Blockly.MutatorPlus(this));    
    this.plusCount_ = 0;
  },
  mutationToDom: function() {
    if (!this.plusCount_) {
        return null;
    }
    var container = document.createElement('mutation');
    if (this.plusCount_) {
        container.setAttribute('plus',this.plusCount_);
    }
    return container;
  },
  domToMutation: function(xmlElement) {
    this.plusCount_ = parseInt(xmlElement.getAttribute('plus'), 10);
    var mytype = this.getInput('A').connection.check_;
    for (var x = 1; x <= this.plusCount_; x++) {
        this.appendStatementInput('PLUS' + x)
            .appendField(Blockscad.Msg.PLUS)
            .setCheck(mytype);
    }
    if (this.plusCount_ >= 1) {
        this.setMutatorMinus(new Blockly.MutatorMinus(this));
    }
  },
  updateShape_ : function(num) {
    if (num == 1) {
      this.plusCount_++;
      var mytype = this.getInput('A').connection.check_;
      var plusInput = this.appendStatementInput('PLUS' + this.plusCount_)
          .appendField(Blockscad.Msg.PLUS)
          .setCheck(mytype); 
    } else if (num == -1) {
      this.removeInput('PLUS' + this.plusCount_); 
      this.plusCount_--;
    }
    if (this.plusCount_ >= 1) {
      if (this.plusCount_ == 1) {
        this.setMutatorMinus(new Blockly.MutatorMinus(this));
        this.render();
      }
    } else {
      this.mutatorMinus.dispose();
      this.mutatorMinus = null;
      this.render();
    }
  },
  setType: function(type) {
    if (!this.workspace) {
      // Block has been deleted.
      return;
    }
    //console.log("setting union type to",type);
    this.previousConnection.setCheck(type);
    this.getInput('A').connection.setCheck(type);
    this.getInput('PLUS0').connection.setCheck(type);
    for (var i = 1; i <= this.plusCount_; i++) {
      this.getInput('PLUS' + i).connection.setCheck(type);
    }
  }   
}; 
Blockly.Blocks['difference'] = {
  init: function() {
    this.category = 'SET_OP';
    this.setHelpUrl('http://www.example.com/');
    this.setColour(Blockscad.Toolbox.HEX_SETOP);
    this.appendDummyInput()
        .appendField(Blockscad.Msg.DIFFERENCE);
    this.appendStatementInput("A")
        .setCheck(["CSG",'CAG']);
    this.appendStatementInput("MINUS0")
        .appendField(Blockscad.Msg.MINUS)
        .setCheck(['CSG','CAG']);
    this.setInputsInline(true);
    this.setPreviousStatement(true, ['CSG','CAG']);
    this.setTooltip(Blockscad.Msg.DIFFERENCE_TOOLTIP);
    // try to set up a mutator - Jennie
    this.setMutatorPlus(new Blockly.MutatorPlus(this));    
    this.minusCount_ = 0;
  },
  mutationToDom: function() {
    if (!this.minusCount_) {
        return null;
    }
    var container = document.createElement('mutation');
    if (this.minusCount_) {
        container.setAttribute('minus',this.minusCount_);
    }
    return container;
  },
  domToMutation: function(xmlElement) {
    this.minusCount_ = parseInt(xmlElement.getAttribute('minus'), 10);
    var mytype = this.getInput('A').connection.check_;
    for (var x = 1; x <= this.minusCount_; x++) {
        this.appendStatementInput('MINUS' + x)
            .appendField(Blockscad.Msg.MINUS)
            .setCheck(mytype);
    }
    if (this.minusCount_ >= 1) {
        this.setMutatorMinus(new Blockly.MutatorMinus(this));
    }
  },
  updateShape_ : function(num) {
    if (num == 1) {
      this.minusCount_++;
      var mytype = this.getInput('A').connection.check_;
      var minusInput = this.appendStatementInput('MINUS' + this.minusCount_)
          .appendField(Blockscad.Msg.MINUS)
          .setCheck(mytype); 
    } else if (num == -1) {
      this.removeInput('MINUS' + this.minusCount_); 
      this.minusCount_--;
    }
    if (this.minusCount_ >= 1) {
      if (this.minusCount_ == 1) {
        this.setMutatorMinus(new Blockly.MutatorMinus(this));
        this.render();
      }
    } else {
      this.mutatorMinus.dispose();
      this.mutatorMinus = null;
      this.render();
    }
  }, 
  setType: function(type) {
    if (!this.workspace) {
      // Block has been deleted.
      return;
    }
    //console.log("setting diff type to",type);
    this.previousConnection.setCheck(type);
    this.getInput('A').connection.setCheck(type);
    this.getInput('MINUS0').connection.setCheck(type);
    for (var i = 1; i
        <= this.minusCount_; i++) {
      this.getInput('MINUS' + i).connection.setCheck(type);
    }
  }   
};
Blockly.Blocks['intersection'] = {
  init: function() {
    this.category = 'SET_OP';
    this.setHelpUrl('http://www.example.com/');
    this.setColour(Blockscad.Toolbox.HEX_SETOP);
    this.appendDummyInput()
        .appendField(Blockscad.Msg.INTERSECTION);
    this.appendStatementInput("A")
        .setCheck(["CSG","CAG"]);
    this.appendStatementInput("WITH0")
        .appendField(Blockscad.Msg.WITH)
        .setCheck(["CSG","CAG"]);
    this.setInputsInline(true);
    this.setPreviousStatement(true, ["CSG",'CAG']);
    this.setTooltip(Blockscad.Msg.INTERSECTION_TOOLTIP);
    this.setMutatorPlus(new Blockly.MutatorPlus(this));    
    this.withCount_ = 0;
  },
  mutationToDom: function() {
    if (!this.withCount_) {
        return null;
    }
    var container = document.createElement('mutation');
    if (this.withCount_) {
        container.setAttribute('with',this.withCount_);
    }
    return container;
  },
  domToMutation: function(xmlElement) {
    this.withCount_ = parseInt(xmlElement.getAttribute('with'), 10);
    var mytype = this.getInput('A').connection.check_;
    for (var x = 1; x <= this.withCount_; x++) {
        this.appendStatementInput('WITH' + x)
            .appendField(Blockscad.Msg.WITH)
            .setCheck(mytype);
    }
    if (this.withCount_ >= 1) {
        this.setMutatorMinus(new Blockly.MutatorMinus(this));
    }
  },
  updateShape_ : function(num) {
    if (num == 1) {
      this.withCount_++;
      var mytype = this.getInput('A').connection.check_;
      var withInput = this.appendStatementInput('WITH' + this.withCount_)
          .appendField(Blockscad.Msg.WITH)
          .setCheck(mytype); 
    } else if (num == -1) {
      this.removeInput('WITH' + this.withCount_); 
      this.withCount_--;
    }
    if (this.withCount_ >= 1) {
      if (this.withCount_ == 1) {
          this.setMutatorMinus(new Blockly.MutatorMinus(this));
          this.render();
      }
    } else {
      this.mutatorMinus.dispose();
      this.mutatorMinus = null;
      this.render();
    }
  },
  setType: function(type) {
    if (!this.workspace) {
      // Block has been deleted.
      return;
    }
    //console.log("setting intersect type to",type);
    this.previousConnection.setCheck(type);
    this.getInput('A').connection.setCheck(type);
    this.getInput('WITH0').connection.setCheck(type);
    for (var i = 1; i
            <= this.withCount_; i++) {
      this.getInput('WITH' + i).connection.setCheck(type);
    }
  }      
};

Blockly.Blocks['hull'] = {
  init: function() {
    this.category = 'SET_OP';
    this.setHelpUrl('http://www.example.com/');
    this.setColour(Blockscad.Toolbox.HEX_SETOP);
    this.appendDummyInput()
        .appendField(Blockscad.Msg.CONVEX_HULL);
    this.appendStatementInput("A")
        .setCheck(["CSG","CAG"]);
    this.appendStatementInput("WITH0")
        .appendField(Blockscad.Msg.WITH)
        .setCheck(["CSG","CAG"]);
    this.setInputsInline(true);
    this.setPreviousStatement(true, ["CSG","CAG"]);
    this.setTooltip(Blockscad.Msg.HULL_TOOLTIP);
    // try to set up a mutator - Jennie
    this.setMutatorPlus(new Blockly.MutatorPlus(this));    
    this.withCount_ = 0;
  },
  mutationToDom: function() {
    if (!this.withCount_) {
        return null;
    }
    var container = document.createElement('mutation');
    if (this.withCount_) {
        container.setAttribute('with',this.withCount_);
    }
    return container;
  },
  domToMutation: function(xmlElement) {
    this.withCount_ = parseInt(xmlElement.getAttribute('with'), 10);
    var mytype = this.getInput('A').connection.check_;
    for (var x = 1; x <= this.withCount_; x++) {
        this.appendStatementInput('WITH' + x)
            .appendField(Blockscad.Msg.WITH)
            .setCheck(mytype);
    }
    if (this.withCount_ >= 1) {
        this.setMutatorMinus(new Blockly.MutatorMinus(this));
    }
  },
  updateShape_ : function(num) {
    if (num == 1) {
      this.withCount_++;
      var mytype = this.getInput('A').connection.check_;
      var withInput = this.appendStatementInput('WITH' + this.withCount_)
          .appendField(Blockscad.Msg.WITH)
          .setCheck(mytype); 
    } else if (num == -1) {
      this.removeInput('WITH' + this.withCount_); 
      this.withCount_--;
    }
    if (this.withCount_ >= 1) {
      if (this.withCount_ == 1) {
          this.setMutatorMinus(new Blockly.MutatorMinus(this));
          this.render();
      }
    } else {
      this.mutatorMinus.dispose();
      this.mutatorMinus = null;
      this.render();
    }
  }, 
  setType: function(type) {
    if (!this.workspace) {
      // Block has been deleted.
      return;
    }
    //console.log("setting union type to",type);
    this.previousConnection.setCheck(type);
    this.getInput('A').connection.setCheck(type);
    this.getInput('WITH0').connection.setCheck(type);
    for (var i = 1; i <= this.withCount_; i++) {
      this.getInput('WITH' + i).connection.setCheck(type);
    }
  } 
};
