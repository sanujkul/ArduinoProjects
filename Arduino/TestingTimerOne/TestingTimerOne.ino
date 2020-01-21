#include <TimerOne.h>

void setup() {
  Timer1.initialize(3000000);
  Timer1.attachInterrupt(whatIsTime); // blinkLED to run every 0.15 seconds
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void whatIsTime(){
  Serial.println(millis());
}

