
#include <Servo.h>  //Using servo library to control ESC

Servo esc;          //Creating an object of Servo

void setup() {
  esc.attach(8);                //Specify ESC pin, here as D9
  esc.writeMicroseconds(1000);  //initialize the signal to 1000
  Serial.begin(9600);           //
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int val;                            //Creating the variable val
  val = analogRead(A0);               //Reading the val from analog pin and store its val
  Serial.println(val);                
  val = map(val,0,1023,1000,2000);    //mapping the val to minimum and maximum input
  Serial.println(val);
  delay(2000);
  esc.writeMicroseconds(val);         //using val as the signal to ESC
}
