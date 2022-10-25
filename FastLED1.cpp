#include <FastLED.h>
#include <stdio.h>
#include <math.h>
#include <arduino.h>
//#include <NightDriver.h>
#include <arduinoFFT.h>
#include <OneButton.h>
#include <ArduinoSTL.h>
#include <plotter.h>

#define LED_PIN 2           // define led output
#define NUM_LEDS 288        //define num of total leds in array.
#define LED_TYPE WS2812B    //led type

/////////////////////////////// PS2 JOYSTICK PART /////////////////////////////////////////////
const int swPin = 10;
const int VrxPin = 5;
const int VryPin = 4;
///
int xDirection = 0;
int yDrection = 0;
int switchState =1;
/////// PS2 button joystick///////////////
OneButton btn = OneButton(swPin,true,true);

////////////////////////MAX9814/////////////////////////////////////////
//uint8_t  MicPin=A0;
//int MicPin = 7;
double Mic_val;
//#define GND2 12

//plotter
Plotter p;

//////////////////////////////////// Global Variables//////////////////////////////
unsigned long  Start_time=0;
CRGB leds[NUM_LEDS]={0}; //Create Led array. sets it to zero so it could do a memset.
uint8_t hue = 0;         //Create a 255 bit int of hue. so it will math the color wheel.
int scene = 0;           //define int called scene for switch case. int is over here so it wont get re written by loop
float density = float(255)/float(NUM_LEDS); //255 hue divide by number of leds, sets a stepping stone for ituration.
int i=0; ///global counter so we can use it and save the definition in the loop section.


// Gradient palette "trove_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/trove.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 84 bytes of program space.

DEFINE_GRADIENT_PALETTE( trove_gp ) {
    0,  12, 23, 11,
   12,   8, 52, 27,
   25,  32,142, 64,
   38,  55, 68, 30,
   51, 190,135, 45,
   63, 201,175, 59,
   76, 186, 80, 20,
   89, 220, 79, 32,
  101, 184, 33, 14,
  114, 137, 16, 15,
  127, 118, 20, 27,
  140,  79, 16, 35,
  153,  67,  8, 26,
  165,  22,  9, 42,
  178,  11,  3, 34,
  191,  58, 31,109,
  204, 186, 49, 83,
  216, 182, 25, 55,
  229,  39, 90,100,
  242,  15, 81,132,
  255,  68,135, 52};

// Gradient palette "angelrepose_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/angelrepose.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( angelrepose_gp ) {
    0, 167, 57, 53,
  255,  12, 90, 99};

  // Gradient palette "scarletdragon_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/scarletdragon.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( scarletdragon_gp ) {
    0,   1,  1,  1,
   51,  16,  2,  1,
   91,  58,  5,  1,
  122, 100, 16,  2,
  150, 120, 33,  9,
  178, 132, 43, 13,
  216, 157, 79, 28,
  255, 227, 92, 29};

CRGBPalette16 MiddlePalette(scarletdragon_gp);
CRGBPalette16 CurrentPalette(angelrepose_gp);
CRGBPalette16 EndPalette(trove_gp);
uint8_t colorindex[NUM_LEDS];
#include <Marquee.h>
#include <Comet.h>
#include <Bounce.h>
#include <Gradient.h>

///functions
void Scene_counter(){
 scene= scene + 1;//because scene is a global variable the function increments it by 1.
}


void setup(){ ///everything here will be defined once in startup.
  FastLED.clear(false); // clear the led but doesnt remove the bytes
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(swPin,INPUT);
  digitalWrite(swPin,HIGH);
  p.Begin();
  p.AddTimeGraph("Mic volume",1500,"mic vol",Mic_val);
//pinMode(GND2,OUTPUT); // gnd2 is output
//digitalWrite(GND2,LOW); // low means gnd
  //pinMode(MicPin,INPUT);

  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS); // Define led type, output and color order for led, in this case its GRB.
  FastLED.setBrightness(150);
  Serial.begin(115200);
  Serial.print("this is the start\n");
  btn.attachClick(Scene_counter);
}


void loop(){
  //BouncingBallEffect balls[NUM_LEDS,1];
   /* xDirection=analogRead(VrxPin);
    yDrection=analogRead(VryPin);
    switchState = digitalRead(swPin);
     Serial.print("this is the button state \n");
    Serial.println(switchState);*/
    if (scene==5)
     scene=0;
    switch (scene)
    {
    case 0:{  // "{}" is for fmpersive problem.
      DrawCommet();}
      break;
    
    case 1:{
      DrawMarquee();
    }break;
    case 2:{
    fill_rainbow(leds,NUM_LEDS,hue += int(3*density),ceil(density)); //the hue equation sets the rate of change in color, random8()*density =epilepsy
    }break;
    case 3:{
      Draw_Grad();
    
      break;
    }
    case 4:
    {
      p.Plot();
      Mic_val=analogRead(A0);
      //Serial.print("this is the mic volume  ");
      //Serial.println(Mic_val);
      //p.Plot();
      //delay(100);
      break;
    }
    /*case 3:{/// doesnt work yet/
       fill_palette(leds,NUM_LEDS,0,ceil(density),CurrentPalette,255,LINEARBLEND );
    //fill_palette(leds,NUM_LEDS,0,ceil(density),EndPalette,255,LINEARBLEND );
    //FastLED.show();
   // for(i=0;i<NUM_LEDS;i++){
      //colorindex[i] = random8();
      //if(i<NUM_LEDS){
       // leds[i]=ColorFromPalette(CurrentPalette,colorindex[i]);
     nblendPaletteTowardPalette(CurrentPalette,EndPalette,5);//}//}
    // nblendPaletteTowardPalette(EndPalette,MiddlePalette,1);
     //nblendPaletteTowardPalette(MiddlePalette,CurrentPalette,1);
    }
    break;*/
    }
    
    FastLED.show();
    btn.tick();
  //}
  /*int key = 1;
  int i;
  Serial.print("this is the density \n");
  Serial.println(density);
  unsigned long timer;
  unsigned long end_timer;
  switch (scene){
  case 0 :{
  fill_gradient_RGB(leds, NUM_LEDS, CRGB::Yellow, CRGB::Magenta); //Yellow and Magenta gradient.
  FastLED.show();
  }break;
  case 1 :{
  Serial.print("fuck me\n");
    //fill_gradient_RGB(leds, NUM_LEDS, CRGB::Green, CRGB::Blue,CRGB::Black);   ///Green Blue gradient
    fill_palette(leds,NUM_LEDS,0,ceil(density),CurrentPalette,255,LINEARBLEND );
    FastLED.show();
    delay(1000);
    //fill_palette(leds,NUM_LEDS,0,ceil(density),EndPalette,255,LINEARBLEND );
    //FastLED.show();
    for(i=0;i<NUM_LEDS;i++){
      colorindex[i] = random8();
      if(i<NUM_LEDS){
       // leds[i]=ColorFromPalette(CurrentPalette,colorindex[i]);
     nblendPaletteTowardPalette(CurrentPalette,EndPalette,10);}}
    FastLED.show();
  }break;
  case 2 :{
  //Serial.print("fuck me number 2\n");
    fill_rainbow(leds, NUM_LEDS, 0, ceil(density)); //Rainbow fill to the led. the density is under celing math function to deal with num leds >> 255.
  FastLED.show();
  }break;
  case 3: {
    timer = millis();
  while (key ==1 ){
    bool bled = 0;       //turns led on and off.
    bled = !bled;
   // Serial.print("hi im here \n");
    digitalWrite (LED_BUILTIN,bled);
    fill_rainbow(leds,NUM_LEDS,hue += int(3*density),ceil(density)); //the hue equation sets the rate of change in color, random8()*density =epilepsy
    FastLED.show();
    unsigned long end_timer = millis();
    if (end_timer-timer>=15000){
    Serial.print("Every N second\n");
    key = 0;}}
   // FastLED.delay();
    //Serial.print("this is a \n");
    //Serial.println(a);//}
    //}
    }break;
    case 4:{// "{}" is for fmpersive problem.
      key = 1;
      timer = millis();
      Serial.print("im here on case 4, ready for the marquee?\n");
      while (key == 1){
      DrawMarquee();
      FastLED.show();
      end_timer = millis();
      if (end_timer-timer>=15000){
    Serial.print("Every N second\n");
    key = 0;}}
    Serial.print("im after the marquee\n");
    }break;
    case 5:{
    key=1;
    timer = millis();
    while (key == 1){
    DrawCommet();
    FastLED.show();
    end_timer = millis();
      if (end_timer-timer>=150000){
    Serial.print("Every N second\n");
    key = 0;}}
    
    }
  }
    key=0;
  delay(1000);
  for ( int i = 0; i < NUM_LEDS; i++) {  //this is the loop for turning off the led 1 by 1.
    leds[i] = CRGB::Black;
    delay(5);
    FastLED.show();
    }
   //while (key == 0){
  for (int i = NUM_LEDS; i >= 0 ; i--) {    //this is the loop for turning on the led 1 by 1 with random RGB colors by hue. every time it runs every led gets a diffrent color.
  leds[i] = CHSV (hue + (7*i+5) ,255,255 );
   FastLED.show();
  delay(5);
  hue++;
          }
    delay(600);
      key=1;
            
  //}
  //EVERY_N_MILLISECONDS(100){ //10 tims a sec scene goes up, but only when the code is here so its almost equevelent to scene++ in a for loop.           
    scene++;            // this makes the starting scene diffrent every run
   Serial.print("value of scene\n");
   Serial.println(scene);
    if (scene > 5){
    scene=0;
    Serial.print("value of scene\n");
    Serial.println(scene);
    }*/
}





