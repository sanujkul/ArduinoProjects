#include <Servo.h>

Servo myservo;  // create servo object to control a servo

//int potpin = 0;  // analog pin used to connect the potentiometer
//int val;    // variable to read the value from the analog pin

int readFromSerial; 
int servoInput;

void setup() {
  Serial.begin(9600);
  Serial.println("Begin");
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
}

void loop() {
//  Serial.println("Send a number please: ");
//  while(!Serial.available()){
//    //Do nothing
//  }
//  int val = Serial.parseInt();
//  Serial.println(val);
//  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
//  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
//  Serial.println(val);
//  myservo.write(val);                  // sets the servo position according to the scaled value
//  delay(15);                           // waits for the servo to get there
//    for(int i=0; i<10; i++){
//      myservo.write(175);
//      delay(1000);
//      myservo.write(0);
//      delay(1000);
//    }

//  Serial.println(val);

//  //Rotate clockwise
//  for(int i=0; i<=9; i++){
//    Serial.println(i*10);
//    myservo.write(i*10);
//    delay(3000);
//    Serial.println("STOP");
//    myservo.write(90); //90 will stop the servo
//    delay(2000);
//  }
//
//  for(int i=0; i<=9; i++){
//    Serial.println((i*10) + 90);
//    myservo.write((i*10) + 90);
//    delay(3000);
//
//    myservo.write(90); //90 will stop the servo
//    delay(2000);
//  }
  
  if (Serial.available() > 0) {

    readFromSerial = Serial.parseInt(); // read the incoming byte:

    if(readFromSerial != 0){
      servoInput = readFromSerial;
    }
    Serial.print(" Servo input is ");

    Serial.println(servoInput);
  }

  myservo.writeMicroseconds(servoInput);
}
