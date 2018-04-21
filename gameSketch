#include <Bounce2.h>


bool swimMode;
bool endGenerated;
const long minSwimTimes = 10;
const long maxSwimTimes = 100;
long randTimesGenerated;
long countCurrentTimes;
const int inputPin = 2;
const int outputPin1 = 3;
const int outputPin2 = 4;
int inputState = 0;
long theShark;

void setup() {
	Serial.begin(9600);
  
  pinMode(inputPin, INPUT);
  pinMode(outputPin1, INPUT);
  pinMode(outputPin2, INPUT);
  swimMode = true;
  endGenerated = false;
  randomSeed(analogRead(0));
}

void loop() {
  if(swimMode){
    if(!endGenerated){
      randTimesGenerated = random(minSwimTimes, maxSwimTimes);
      countCurrentTimes = 0;
      endGenerated = !endGenerated;
      Serial.print("rand generated: ");
      Serial.println(randTimesGenerated);
    }
    
    if(inputState != digitalRead(inputPin)){
      countCurrentTimes++;
      Serial.print("count times: ");
      Serial.println(countCurrentTimes);
      inputState = !inputState;
    }
    if(countCurrentTimes >= randTimesGenerated){
      swimMode = !swimMode;
    }
  }else{
    Serial.println("out of swimMode");
    theShark = random(1,3);
    if(digitalRead(theShark)){
      //bite
    }
    swimMode = !swimMode;
    endGenerated = !endGenerated;
    countCurrentTimes = -1;
  }
  delay(50);//will delete
}

/*test area
long randnum;
void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0));
 
}

void loop(){
    randnum = random(1,3);
    Serial.println(randnum);
    delay(1000);
}

