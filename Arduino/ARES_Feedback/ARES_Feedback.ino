#include <LiquidCrystal.h>

#define encoderPin0 2
#define encoderPin1 3
#define encoderPin2 18
#define encoderPin3 19

#define raspiPin0 8
#define raspiPin1 9
#define raspiPin2 10
#define raspiPin3 11

float countInOneRotation = 6000;

int count[4];
int startingCount[4];
float velocity[4];

int timestart = 0;

////////////////////////////////////////////////
////////////// LCD /////////////////////////////
////////////////////////////////////////////////
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void printOnLCD(String data1, String data2){
  lcd.setCursor(0, 1);
  lcd.print(data1);

  lcd.setCursor(1, 1);
  lcd.print(data2);
}
////////////////////////////////////////////////
////////////////////////////////////////////////

void raiseCount0(){
  count[0]++;
}
void raiseCount1(){
  count[1]++;
}
void raiseCount2(){
  count[2]++;
}
void raiseCount3(){
  count[3]++;
}

void setup() {
  lcd.begin(16, 2);
  attachInterrupt(digitalPinToInterrupt(encoderPin0), raiseCount0, CHANGE); //Attaching the interrupts
  attachInterrupt(digitalPinToInterrupt(encoderPin1), raiseCount1, CHANGE); //Attaching the interrupts
  attachInterrupt(digitalPinToInterrupt(encoderPin2), raiseCount2, CHANGE); //Attaching the interrupts
  attachInterrupt(digitalPinToInterrupt(encoderPin3), raiseCount3, CHANGE); //Attaching the interrupts
}

void loop() {
  
  for(int i=0; i<4; i++){
      startingCount[i] = count[i];
  }
  timestart = micros();
  
  if(count[0] > 10000 || count[1] > 10000 || count[2] > 10000 || count[3] > 10000){
    for(int i=0; i<4; i++){
      count[i] = count[i] - 10000;
    }
  }
  while(micros() - timestart < 100000){ //100 milli seconds
    //Do nothing 
  }
  
  for(int i=0; i<4; i++){
      velocity[i] = (((count[i]-startingCount[i])/countInOneRotation)/0.1)*60; //THIS IS RPM (0.1 = time in sec, 60 is converting to minutes)
    }
}
