//This code is made by the drunken version of yuval grimberg.
//this header file is Gradient.h Is inspired by Scott Marley EP3.

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h> //included multiple times for saftey and intellisene

//#define NUM_LEDS 288
extern CRGB leds[];

  CRGBPalette16 purplePalette = CRGBPalette16 (
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    
    CRGB::Magenta,
    CRGB::Magenta,
    CRGB::Linen,
    CRGB::Linen,

    CRGB::Magenta,
    CRGB::Magenta,
    CRGB::DarkViolet,
    CRGB::DarkViolet,

    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::Linen,
    CRGB::Linen
);

// Gradient palette "ibcao_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ibcao/tn/ibcao.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 188 bytes of program space.

DEFINE_GRADIENT_PALETTE( ibcao_gp ) {
    0,   2, 16, 63,
   39,   2, 16, 63,
   39,   1, 42, 88,
   79,   1, 42, 88,
   79,   1, 55,119,
   99,   1, 55,119,
   99,   1, 67,140,
  119,   1, 67,140,
  119,   1, 93,164,
  139,   1, 93,164,
  139,   1,122,178,
  159,   1,122,178,
  159,   2,136,255,
  179,   2,136,255,
  179,   5,141,174,
  191,   5,141,174,
  191,   6,141,164,
  195,   6,141,164,
  195,   7,139,151,
  197,   7,139,151,
  197,   8,139,128,
  198,   8,139,128,
  198,  26,149,123,
  198,  26,149,123,
  198,  67,169,123,
  199,  67,169,123,
  199, 167,175, 13,
  201, 167,175, 13,
  201, 213,197, 29,
  203, 213,197, 29,
  203, 215,159, 19,
  207, 215,159, 19,
  207, 192,133, 14,
  211, 192,133, 14,
  211, 167, 95,  5,
  215, 167, 95,  5,
  215, 123, 69,  6,
  219, 123, 69,  6,
  219, 107, 57,  6,
  223, 107, 57,  6,
  223,  95, 51,  5,
  227,  95, 51,  5,
  227,  84, 45,  5,
  231,  84, 45,  5,
  231,  64, 33,  4,
  239,  64, 33,  4,
  255, 255,255,255};



CRGBPalette16 myPal = ibcao_gp;

//extern CRGB leds[];
//CRGBPalette16 MiddlePalette(scarletdragon_gp);
//CRGBPalette16 CurrentPalette(angelrepose_gp);
//CRGBPalette16 EndPalette(trove_gp);
///uint8_t colorindex[NUM_LEDS];

void Draw_Grad(){
  
  
    //Switch on an LED at random, choosing a random color from the palette
    leds[random16(0, NUM_LEDS - 1)] = ColorFromPalette(myPal, random16(0, NUM_LEDS - 1), 255, LINEARBLEND);
  

   // Fade all LEDs down by 1 in brightness each time this is called
   fadeToBlackBy(leds, NUM_LEDS, 1);
   EVERY_N_SECONDS(15){

   EVERY_N_MILLISECONDS(358){
    myPal = CurrentPalette;
   
   EVERY_N_MILLISECONDS(1500){
    myPal = EndPalette;
   }
   }
   }
  //FastLED.show();

  EVERY_N_SECONDS(7){
    myPal = purplePalette;
  }
}
