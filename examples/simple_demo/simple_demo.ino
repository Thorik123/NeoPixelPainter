/**
   Simple animation demo for using the NoePixel painter library
   This demo does the Knight Rider scanner effect with just a few lines of code
   The speed and fadespeed need to be adjusted for different processor speeds
   Chosen settings work nicely on 60-pixels and an Arduino Duemilenove
*/

#define NUMBEROFPIXELS 60 //Number of LEDs on the strip
#define PIXELPIN 2 //Pin where WS281X LED strip data-line is connected

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <NeoPixelPainter.h>


Adafruit_NeoPixel neopixels = Adafruit_NeoPixel(NUMBEROFPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);

//create one canvas and one brush with global scope
NeoPixelPainterCanvas pixelcanvas = NeoPixelPainterCanvas(&neopixels); //create canvas, linked to the neopixels (must be created before the brush)
NeoPixelPainterBrush pixelbrush = NeoPixelPainterBrush(&pixelcanvas); //crete brush, linked to the canvas to paint to


void setup() {

  pinMode(PIXELPIN, OUTPUT);

  neopixels.begin();

  Serial.begin(115200);
  Serial.println(" ");
  Serial.println(F("NeoPixel Painter simple demo"));

  //check if ram allocation of brushes and canvases was successful (painting will not work if unsuccessful, program should still run though)
  //this check is optional but helps to check if something does not work, especially on low ram chips like the Arduino Uno
  if (pixelcanvas.isvalid() == false) Serial.println(F("canvas allocation problem (out of ram, reduce number of pixels)"));
  else  Serial.println(F("canvas allocation ok"));

  if (pixelbrush.isvalid() == false) Serial.println(F("brush allocation problem"));
  else  Serial.println(F("brush allocation ok"));

  //initialize the animation, this is where the magic happens:

  HSV brushcolor;
  brushcolor.h = 0; //zero is red in HSV. Library uses 0-255 instead of 0-360 for colors (see https://en.wikipedia.org/wiki/HSL_and_HSV)
  brushcolor.s = 255; //full color saturation
  brushcolor.v = 130; //about half the full brightness

  pixelbrush.setSpeed(2000); //set the brush movement speed (4096 means to move one pixel per update)
  pixelbrush.setColor(brushcolor); //set the brush color
  pixelbrush.setFadeSpeed(200); //fading speed of pixels (255 max, 200 is fairly fast)
  pixelbrush.setFadeout(true); //do brightness fadeout after painting
  pixelbrush.setBounce(true); //bounce the brush when it reaches the end of the strip

}

void loop() {
  neopixels.clear(); //always need to clear the pixels, the canvas' colors will be added to whatever is on the pixels before calling an canvas update

  pixelbrush.paint(); //paint the brush to the canvas (and update the brush, i.e. move it a little)
  pixelcanvas.transfer(); //transfer the canvas to the neopixels

  neopixels.show();
}