//This code is made by the Semi Sober version of yuval grimberg.
//this header file is Comet.h inspired by Daves garage FastLED tutorial ep 6

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h> //included multiple times for saftey and intellisene



extern CRGB leds[];
void DrawCommet (){

const byte fadeAmt = 128; //fraction of 256 to fade a pixel if its chosen to be faded
const int cometSize = 5; //size of comet in pixels
const int deltaHue = 4; //how fast it changes the color.

static byte hue = HUE_RED; //current color
static int Direction = 1; // current direction -1 or 1.
static int ipos = 0; // initial position

hue += deltaHue;
ipos += Direction;

if(ipos == (NUM_LEDS - cometSize) || ipos == 0)
Direction*=-1;

// Draw the comet at is current pos
for(int i=0;i<cometSize;i++)
leds[ipos+i].setHue(hue);

// Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS; j++)
        if (random(10) > 5)
            leds[j] = leds[j].fadeToBlackBy(fadeAmt);  

    delay(10);
}