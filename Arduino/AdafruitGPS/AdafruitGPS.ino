#include <TinyGPS++.h>
static const uint32_t GPSBaud = 9600;

#include <Adafruit_GPS.h>    //Install the adafruit GPS library
//
//SoftwareSerial mySerial(3,2); //Initialize the Software Serial port
Adafruit_GPS GPS(&Serial3); //Create the GPS Object

String NMEA1; //Variable for first NMEA sentence
String NMEA2; //Variable for second NMEA sentence
String NMEA3; //Variable for first NMEA sentence
String NMEA4; //Variable for first NMEA sentence
String NMEA5; //Variable for first NMEA sentence
char c; //to read characters coming from the GPS

void setup() {
  // put your setup code here, to run once:
//  Serial3.begin(9600);
  Serial.begin(9600);

  GPS.begin(9600); //Turn on GPS at 9600 baud
  GPS.sendCommand("$PGCMD,33,0*6D");  //Turn off antenna update nuisance data
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Request RMC and GGA Sentences only
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //Set update rate to 1 hz
  delay(1000); //Pause

  
}

String glatitute = "";
String glongitude = "";
String galtitude = "";
String gsat = "";
String gtime = "";
void loop() {
  // put your main code here, to run repeatedly:
  readGPS();  //This is a function we define below which reads two NMEA sentences from GPS

  
    glatitute = String(GPS.latitude,6);
    glongitude = String(GPS.longitude,6);
    galtitude = String(GPS.altitude);
    gsat = String(GPS.satellites);
    gtime = String(GPS.hour)+":"+String(GPS.minute)+":"+String(GPS.seconds);

//    String GPSPacket = glatitute +"\t"+ glongitude +"\t"+ galtitude +"\t"+ gsat +"\t"+ gtime;
//    Serial.println(GPSPacket+"\n ========== \n");
    
    String GPSPacket2 = getLatLongInFormat(glatitute) +"\t"+ getLatLongInFormat(glongitude) +"\t"+ galtitude +"\t"+ gsat +"\t"+ gtime;    
    Serial.println(GPSPacket2+"\n ========== \n");
    
    delay(500);
  
}

String getLatLongInFormat(String latLong){
  int decimalPosition = latLong.indexOf('.');
  String GPSdegrees = latLong.substring(0,decimalPosition-2);
  String minutes = latLong.substring(decimalPosition-2);

  float minutesFloat = (minutes.toFloat())/60;

//  Serial.println(minutesFloat,4);
  
  String GPSMinutes = String(minutesFloat,4);
  int decimalPositionMinutes = GPSMinutes.indexOf('.');
  
  String toReturn = GPSdegrees+GPSMinutes.substring(decimalPositionMinutes);

  return toReturn;
  
}


void readGPS(){  //This function will read and remember two NMEA sentences from GPS
  clearGPS();    //Serial port probably has old or corrupt data, so begin by clearing it all out
  //1.
  while(!GPS.newNMEAreceived()) { //Keep reading characters in this loop until a good NMEA sentence is received
    c=GPS.read(); //read a character from the GPS
  }
  GPS.parse(GPS.lastNMEA());  //Once you get a good NMEA, parse it
  NMEA1=GPS.lastNMEA();      //Once parsed, save NMEA sentence into NMEA1
  //2.
  while(!GPS.newNMEAreceived()) {  //Go out and get the second NMEA sentence, should be different type than the first one read above.
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  NMEA2=GPS.lastNMEA();

  while(!GPS.newNMEAreceived()) {  //Go out and get the second NMEA sentence, should be different type than the first one read above.
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  NMEA3=GPS.lastNMEA();

  while(!GPS.newNMEAreceived()) {  //Go out and get the second NMEA sentence, should be different type than the first one read above.
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  NMEA4=GPS.lastNMEA();

  while(!GPS.newNMEAreceived()) {  //Go out and get the second NMEA sentence, should be different type than the first one read above.
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  NMEA5=GPS.lastNMEA();
  
//  Serial.println(NMEA1);
//  Serial.println(NMEA2);
//  Serial.println(NMEA3);
//  Serial.println(NMEA4);
//  Serial.println(NMEA5);
//  Serial.println("");
}
void clearGPS() {  //Since between GPS reads, we still have data streaming in, we need to clear the old data by reading a few sentences, and discarding these
  //1.
  while(!GPS.newNMEAreceived()) {
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  
  //2.
  while(!GPS.newNMEAreceived()) {
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  
  //3.
  GPS.parse(GPS.lastNMEA());
  while(!GPS.newNMEAreceived()) {
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  
  //4.
  GPS.parse(GPS.lastNMEA());
  while(!GPS.newNMEAreceived()) {
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA());
  
  //5.
//  GPS.parse(GPS.lastNMEA());
//  while(!GPS.newNMEAreceived()) {
//    c=GPS.read();
//  }
//  GPS.parse(GPS.lastNMEA());
 
}
