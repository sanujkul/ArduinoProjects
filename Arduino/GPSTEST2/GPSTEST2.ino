#include <TinyGPS++.h>
//#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);
#define ss Serial3

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat());
      Serial.print(" Longitude= "); 
      Serial.print(gps.location.lng());
      Serial.print(" Satelite= "); 
      Serial.println(gps.satellites.value());
      
    }
  }
//  Serial.println("LOOP ENDS");
}
