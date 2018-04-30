#include <Bounce2.h>
#include <FastLED.h>

//led strip
#define LED_PIN1     5
#define LED_PIN2     6
#define NUM_LEDS    50
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB oceanleds[NUM_LEDS];
CRGB scoreleds[NUM_LEDS];
#define UPDATES_PER_SECOND 100

bool swimMode;
bool endGenerated;
const long minSwimTimes = 10;             //the range of the random num
const long maxSwimTimes = 100;
long randTimesGenerated;                  //the rand
long countCurrentTimes;
const int inputPin1 = 2;                   //tilt switch1
const int inputPin2 = 3;                   //tilt switch2
const int inputPin3 = 3;                   //tilt switch3
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 
const int musicPin = 7;
const int bitePin1 = 8;                 //player 1
const int bitePin2 = 9;                 //player 2
const int bitePin3 = 10;                 //player 3
const int outputPin1 = 11;                 //player 1
const int outputPin2 = 12;                 //player 2
const int outputPin3 = 13;                 //player 3
long theShark;                            //who is the shark
unsigned long timer;                      //record how much time used for a bite
int score1 = 0;                         //player1's score
int score2 = 0;                         //player2's score
int score3 = 0;                         //player3's score

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
  delay(1500);                        // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(oceanleds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(scoreleds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  
	Serial.begin(9600);
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
  pinMode(inputPin3, INPUT);
  pinMode(bitePin1, INPUT);
  pinMode(bitePin2, INPUT);
  pinMode(bitePin3, INPUT);
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  pinMode(outputPin3, OUTPUT);
  pinMode(musicPin, OUTPUT);
  
  swimMode = true;
  endGenerated = false;
  randomSeed(analogRead(0));                //set analog 0 as random seed
  digitalWrite(outputPin1, LOW);
  digitalWrite(outputPin2, LOW);
  digitalWrite(outputPin3, LOW);
  digitalWrite(musicPin, HIGH);
  //debouncer
  debouncer1.attach(inputPin1);
  debouncer2.attach(inputPin2);
  debouncer3.attach(inputPin3);
  debouncer1.interval(10);                   // interval in ms. change from 5 to 25
  debouncer2.interval(10);
  debouncer3.interval(10);
}

void loop() {
  //swim
  if(swimMode){

    /*
     * for test, will delete
     */
    if (Serial.available() > 0) {           
      char inChar = Serial.read();
      if(inChar == '1'){
        score1++;
      }else if(inChar == '2'){
        score2++;
      }else if(inChar == '3'){
        score3++;
      }else if(inChar == '4'){
        score1 = 0;
        score2 = 0;
        score3 = 0;
      }
    }
    
    if(!endGenerated){                        //generate a random number
      digitalWrite(musicPin, HIGH);
      digitalWrite(outputPin1, LOW);
      digitalWrite(outputPin2, LOW);
      digitalWrite(outputPin3, LOW);
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
    debouncer3.update();
    if(debouncer1.fell() || debouncer2.fell() || debouncer3.fell()){
      countCurrentTimes++;
      Serial.print("count times: ");
      Serial.println(countCurrentTimes);
    }
    if(countCurrentTimes >= randTimesGenerated){            //time to bite
      swimMode = !swimMode;
      Serial.println("out of swimMode");
    }
    ledStripEntrance(1, score1, score2, score3);                                  //swim
    
  //bite
  }else{
    if(theShark == 0){
      theShark = random(8,11);              //who is the shark
      digitalWrite(musicPin, LOW);
      Serial.print("theShark: ");
      Serial.println(theShark);
      timer = millis();
    }

    
    
    if(digitalRead(theShark)){              //bite!
        if(theShark == 8){
          score1++;
        }else if(theShark == 9){
          score2++;
        }else{
          score3++;
        }
        swimMode = !swimMode;
        endGenerated = !endGenerated;
        countCurrentTimes = -1;
        theShark = 0;
    }

     /*
     * for test, will delete
     */
    if (Serial.available() > 0) {           
      char inChar = Serial.read();
      if(inChar == 'a'){
        swimMode = !swimMode;
        endGenerated = !endGenerated;
        countCurrentTimes = -1;
        theShark = 0;
      }
    }

    if(theShark == 8){                      //led play mode
      ledStripEntrance(2, score1, score2, score3);
      digitalWrite(outputPin1, HIGH);
    }else if(theShark == 9){
      ledStripEntrance(3, score1, score2, score3);
      digitalWrite(outputPin2, HIGH);
    }else if(theShark == 10){
      ledStripEntrance(4, score1, score2, score3);
      digitalWrite(outputPin3, HIGH);
    }

    if(millis() - timer > 6000){            //more than 6s used
        swimMode = !swimMode;
        endGenerated = !endGenerated;
        countCurrentTimes = -1;
        theShark = 0;
    }
  }
}


void ledStripEntrance(int ledMode, int score1, int score2, int score3){
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors(startIndex, ledMode, score1, score2, score3);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex, int ledMode, int score1, int score2, int score3){
    uint8_t brightness = 255;
    for( int i = 0; i < NUM_LEDS; i++) {
        if(ledMode == 1){
            oceanleds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        }else if(ledMode == 2){
          if(i <= 4){
            oceanleds[i] = CHSV( HUE_RED, 255, 255);
          }else{
            oceanleds[i] = CHSV( HUE_GREEN, 255, 255);
          }
        }else if(ledMode == 3){
          if(i >= 5 && i <= 9){
            oceanleds[i] = CHSV( HUE_RED, 255, 255);
          }else{
            oceanleds[i] = CHSV( HUE_GREEN, 255, 255);
          }
        }else if(ledMode == 4){
          if(i >= 10){
            oceanleds[i] = CHSV( HUE_RED, 255, 255);
          }else{
            oceanleds[i] = CHSV( HUE_GREEN, 255, 255);
          }
        }
        colorIndex += 3;
    }
    for(int i = 0; i < NUM_LEDS; i++){
      if(i < 5){
        if(i < score1){
          scoreleds[i] = CHSV( HUE_GREEN, 255, 255);
        }else{
          scoreleds[i] = CHSV( HUE_GREEN, 0, 0);
        }
      }else if(i < 10){
        if(i - 5 < score2){
          scoreleds[i] = CHSV( HUE_GREEN, 255, 255);
        }else{
          scoreleds[i] = CHSV( HUE_GREEN, 0, 0);
        }
      }else{
        if(i - 10 < score3){
          scoreleds[i] = CHSV( HUE_GREEN, 255, 255);
        }else{
          scoreleds[i] = CHSV( HUE_GREEN, 0, 0);
        }
      }
      
    }
}


