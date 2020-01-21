#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (ss.available() > 0){
  gps.encode(ss.read());
  double gps_altitude = getGPSAltitude();
  int32_t gps_time = getGPSTime();
  double gps_longitude = getGPSLongitude();
  double gps_lattitude = getGPSLatitute();
  int gps_sats = getGPSNumSatelite();

  Serial.print(gps_altitude);
  Serial.print("  ");
  Serial.print(gps_time);
  Serial.print("  ");
  Serial.print(gps_longitude);
  Serial.print("  ");
  Serial.print(gps_lattitude);
  Serial.print("  ");
  Serial.print(gps_sats);
  Serial.println("  ");
  
  delay(1000);
  }
}

int getGPSNumSatelite(){
  if (gps.satellites.isValid()) {
    return gps.satellites.value();
  } else {
  return 0;
  }
}

double getGPSLatitute(){
  if (gps.location.isValid()) {
    return gps.location.lat();
  } else {
  return 0;
  }
}

double getGPSLongitude(){
  if (gps.location.isValid()) {
    return gps.location.lng();
  } else {
  return 0;
  }
}

int32_t getGPSTime(){
  return gps.time.value();
}

double getGPSAltitude(){
  if (gps.altitude.isValid()) {
    return gps.altitude.meters();
  } else {
  return 0;
  }
}
