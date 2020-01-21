/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 */
 
//#include <SoftwareSerial.h>

// The serial connection to the GPS module
//SoftwareSerial ss(4, 3);

#define ss Serial3

void setup(){
  Serial.begin(9600);
  while(!Serial);
  Serial.println("BEGIN");
  ss.begin(9600);
}

void loop(){
//  Serial.println("IN LOOP");
//  Serial.println(ss.available());
  while (ss.available() > 0){
    // get the byte data from the GPS
    byte gpsData = ss.read();
    Serial.write(gpsData);
  }
}
