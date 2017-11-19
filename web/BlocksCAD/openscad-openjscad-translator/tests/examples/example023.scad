// Example combining MCAD/fonts.scad with search() function.

use <MCAD/fonts.scad>

thisFont=8bit_polyfont();
x_shift=thisFont[0][0];
y_shift=thisFont[0][1];

hours=["one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve"];

module clock_hour_words(word_offset=20.0,word_height=2.0) {
  for(i=[0:(len(hours)-1)]) assign( hourHandAngle=(i+1)*360/len(hours), theseIndicies=search(hours[i],thisFont[2],1,1) ) {
    rotate(90-hourHandAngle) translate([word_offset,0])
      for( j=[0:(len(theseIndicies)-1)] ) translate([j*x_shift,-y_shift/2]) {
        linear_extrude(height=word_height) polygon(points=thisFont[2][theseIndicies[j]][6][0],paths=thisFont[2][theseIndicies[j]][6][1]);
      }
  }
}

clock_hour_words(word_offset=16.0,word_height=5.0);
