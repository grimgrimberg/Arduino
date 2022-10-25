//This code is made by the drunken version of yuval grimberg.
//this header file is marquee.h inspired by Daves garage FastLED tutorial ep 5

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h> //included multiple times for saftey and intellisene

void DrawMarquee(){
    static byte j= HUE_AQUA;
    j +=4;
    byte k = j ;

    CRGB c;
    for (int i=0;i<NUM_LEDS;i++){
        leds[i]=c.setHue(k+=7);}

        static int scroll =0;
        scroll ++;
        for(int i=scroll%7;i<NUM_LEDS-1;i+=7){
        leds[i]=CRGB::Black;}
        delay(50);
   
    
}

