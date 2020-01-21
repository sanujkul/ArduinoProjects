#include <LiquidCrystal.h>

#define encoderPin0 2
#define encoderPin1 3
#define encoderPin2 18
#define encoderPin3 19

//const int rs = 22, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int count[4]={0,0,0,0};

void raiseCount0(){
  count[0]++;
  count[0] = count[0] % 10000;
}
void raiseCount1(){
  count[1]++;
  count[1] = count[1] % 10000;
}
void raiseCount2(){
  count[2]++;
  count[2] = count[2] % 10000;
}
void raiseCount3(){
  count[3]++;
  count[3] = count[3] % 10000;
}

void setup() {
  Serial.begin(9600);
  pinMode(encoderPin0, INPUT);
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  pinMode(encoderPin3, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPin0), raiseCount0, CHANGE); //Attaching the interrupts
  attachInterrupt(digitalPinToInterrupt(encoderPin1), raiseCount1, CHANGE); //Attaching the interrupts
  attachInterrupt(digitalPinToInterrupt(encoderPin2), raiseCount2, CHANGE); //Attaching the interrupts
  attachInterrupt(digitalPinToInterrupt(encoderPin3), raiseCount3, CHANGE); //Attaching the interrupts
  
}

void loop() {
  Serial.println(String(count[0])+"\t"+String(count[1])+"\t"+String(count[2])+"\t"+String(count[3]));

}
