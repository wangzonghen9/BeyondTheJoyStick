#include <Bounce2.h>
#include <FastLED.h>

//led strip
#define LED_PIN     5
#define NUM_LEDS    50
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define UPDATES_PER_SECOND 100

bool swimMode;
bool endGenerated;
const long minSwimTimes = 10;             //the range of the random num
const long maxSwimTimes = 100;
long randTimesGenerated;                  //the rand
long countCurrentTimes;
const int inputPin1 = 2;                   //tilt switch1
const int inputPin2 = 3;                   //tilt switch2
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
const int bitePin1 = 8;                 //player 1
const int bitePin2 = 9;                 //player 2
const int outputPin1 = 11;                 //player 1
const int outputPin2 = 12;                 //player 2
long theShark;                            //who is the shark

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
  delay(3000);                        // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  
	Serial.begin(9600);
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
  pinMode(bitePin1, INPUT);
  pinMode(bitePin2, INPUT);
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  
  swimMode = true;
  endGenerated = false;
  randomSeed(analogRead(0));                //set analog 0 as random seed
  digitalWrite(outputPin1, LOW);
  digitalWrite(outputPin2, LOW);
  //debouncer
  debouncer1.attach(inputPin1);
  debouncer2.attach(inputPin2);
  debouncer1.interval(10);                   // interval in ms. change from 5 to 25
  debouncer2.interval(10);
}

void loop() {
  //swim
  if(swimMode){
    
    if(!endGenerated){                        //generate a random number
      digitalWrite(outputPin1, LOW);
      digitalWrite(outputPin2, LOW);
      randTimesGenerated = random(minSwimTimes, maxSwimTimes);
      countCurrentTimes = 0;
      endGenerated = !endGenerated;
      Serial.print("rand generated: ");
      Serial.println(randTimesGenerated);
      currentPalette = OceanColors_p;           //set led strip to ocean color
      currentBlending = LINEARBLEND;
    }
    debouncer1.update();                     //the debouncer
    debouncer2.update();
    if(debouncer1.fell() || debouncer2.fell()){
    //if(debouncer1.fell()){
      countCurrentTimes++;
      Serial.print("count times: ");
      Serial.println(countCurrentTimes);
    }
    if(countCurrentTimes >= randTimesGenerated){            //time to bite
      swimMode = !swimMode;
      Serial.println("out of swimMode");
    }
    ledStripEntrance(1);                                  //swim
    
  //bite
  }else{
    if(theShark == 0){
      theShark = random(8,10);              //who is the shark
      Serial.print("theShark: ");
      Serial.println(theShark);
    }
    
    if(digitalRead(theShark)){              //bite! start again
        swimMode = !swimMode;
        endGenerated = !endGenerated;
        countCurrentTimes = -1;
        theShark = 0;
    }

    //for test
    if (Serial.available() > 0) {           //can start again by keyboard input
      char inChar = Serial.read();
      if(inChar == 'a'){
        swimMode = !swimMode;
        endGenerated = !endGenerated;
        countCurrentTimes = -1;
        theShark = 0;
      }
    }

    if(theShark == 8){                      //led play mode
      ledStripEntrance(2);
      digitalWrite(outputPin1, HIGH);
    }else{
      ledStripEntrance(3);
      digitalWrite(outputPin2, HIGH);
    }
  }
}


void ledStripEntrance(int ledMode){
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors(startIndex, ledMode);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex, int ledMode){
    uint8_t brightness = 255;
    for( int i = 0; i < NUM_LEDS; i++) {
        if(ledMode == 1){
          leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        }else if(ledMode == 2){
          if(i >= 8){
            leds[i] = CHSV( HUE_GREEN, 255, 255);
          }else{
            leds[i] = CHSV( HUE_RED, 255, 255);
          }
        }else{
          if(i >= 8){
            leds[i] = CHSV( HUE_RED, 255, 255);
          }else{
            leds[i] = CHSV( HUE_GREEN, 255, 255);
          }
        }
        colorIndex += 3;
    }
}


