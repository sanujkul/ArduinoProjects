#define enA 9
#define in1 4
#define in2 5

#define enB 10
#define in3 6
#define in4 7

int motorSpeedA = 0;       // To be set by RC
int motorSpeedB = 0;       // To be set by RC

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  //Set motorSpeedA and MotorSpeedB from RC

   if(motorSpeedA >= 0){
      //Forward Motion
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, motorSpeedA);
   }else{
      //Backward Motion
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, -1*(motorSpeedA));
   }

}
