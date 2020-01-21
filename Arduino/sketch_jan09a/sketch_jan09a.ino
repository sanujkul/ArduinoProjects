
#define encoderPin0 19
#define encoderPin1 3
#define encoderPin2 18
#define encoderPin3 2

int count0 = 0;
int startingCount0 = 0;
float velocity0 = 0;
int timestart = 0;

float countInOneRotation = 6000;

void raiseCount0(){
  count0++;
}

void setup() {
  Serial.begin(9600);
  pinMode(encoderPin0, INPUT);
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  pinMode(encoderPin3, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPin0), raiseCount0, CHANGE); //Attaching the interrupts
}

void loop() {
  startingCount0 = count0;
//  int data0 = digitalRead(encoderPin0);
//  int data1 = digitalRead(encoderPin1);
//  int data2 = digitalRead(encoderPin2);
//  int data3 = digitalRead(encoderPin3);

//  Serial.println(data0);
//  Serial.println(data1);
//  Serial.println(data2);
//  Serial.println(data3);
  timestart = millis();

  if(count0 > 100000){
    count0 = count0 % 100000;
  }
  
  while(millis() - timestart < 100){ //100 milli seconds
    //Do nothing 
  }
  
  Serial.print(String(count0) + "\t");
  
  velocity0 = ((((count0-startingCount0)/countInOneRotation)/0.1)*60); //THIS IS RPM (0.1 = time in sec, 60 is converting to minutes)
  
  Serial.println(velocity0);
  
}
