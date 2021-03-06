#include <Wire.h> 

int accelX, accelY, accelZ;    
float gForceX, gForceY, gForceZ;    //stores acceleration in 3 directions in terms ofg

float angleY=0,angleZ=0 ;          
long lastloop=0;

int gyroX, gyroY, gyroZ;        
float rotX, rotY, rotZ;           //This will be storing rotational speed or velocity around those axis

float rollCanSat=0,pitchCanSat=0;

float rollCanSatOffset = 0;
float pitchCanSatOffset = 0;

float gForceXNormalised=0,gForceYNormalised=0,gForceZNormalised=0;
float Xacc[10],Yacc[10],Zacc[10];
float Xgyr[10],Ygyr[10],Zgyr[10];

#define MPU9250ADDRESS 0b1101001

void mpuInIt(){
  initializeValues();
  
//  Wire.setClock(400000);
  setupMPU();
//  callibrateMPU();
}

void initializeValues(){
  accelX = 0; accelY = 0; accelZ = 0;    
  gForceX = 0, gForceY = 0, gForceZ = 0;
  angleY=0;angleZ=0;          
  lastloop=0;
  gyroX = 0; gyroY = 0; gyroZ = 0;        
  rotX = 0; rotY = 0; rotZ = 0;
  rollCanSat=0;pitchCanSat=0;
  rollCanSatOffset = 0;
  pitchCanSatOffset = 0;
  gForceXNormalised=0,gForceYNormalised=0,gForceZNormalised=0;
}

void callibrateMPU(){

  double rollCanSatSum = 0;
  double pitchCanSatSum = 0;

  for(int i=0; i<2000; i++){
    recordAccelRegisters();
    recordGyroRegisters();
    printData();
    rollCanSatSum += rollCanSat;
    pitchCanSatSum += pitchCanSat;
    if(i%20 == 0) Serial.print(".");
  }
  rollCanSatOffset = rollCanSatSum/2000;
  pitchCanSatOffset = pitchCanSatSum/2000;
}

/*
 * Seting up power register and waking up from sleep
 * Setting Aceelerometer to read full range +/-2g = 19.6 m/s2
 * Setting up Gyro to read max full range  +/-250 deg/s
 */

void setupMPU(){
  Serial.println("In SetUpMPU");
  Wire.beginTransmission(MPU9250ADDRESS); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission(); 
   
  Wire.beginTransmission(MPU9250ADDRESS); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission();
   
  Wire.beginTransmission(MPU9250ADDRESS); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
     
}

void recordAccelRegisters() {
  Wire.beginTransmission(MPU9250ADDRESS); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(MPU9250ADDRESS,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;

  gForceXNormalised = gForceX/sqrt(gForceY*gForceY+gForceX*gForceX+gForceZ*gForceZ);
  gForceYNormalised = gForceY/sqrt(gForceY*gForceY+gForceX*gForceX+gForceZ*gForceZ);
  gForceZNormalised = gForceZ/sqrt(gForceY*gForceY+gForceX*gForceX+gForceZ*gForceZ);
}

void recordGyroRegisters() {
  Wire.beginTransmission(MPU9250ADDRESS); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(MPU9250ADDRESS,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printData() {
  //Enable low pass

 for(int i=0;i<10;i++)
 {
  recordAccelRegisters();
  recordGyroRegisters();
 
  
  Xacc[i]=gForceXNormalised;
  Yacc[i]=gForceYNormalised;
  Zacc[i]=gForceZNormalised;

  Xgyr[i]=rotX;
  Ygyr[i]=rotY;
  Zgyr[i]=rotZ;
  
  }

  lastloop=micros();
  for(int i=0;i<10;i++)
  {
    rollCanSat=0.9*(rollCanSat+Xgyr[i]*(micros()-lastloop)/1000000)+0.1*180*atan2(Yacc[i],Zacc[i])/3.14;

    pitchCanSat=0.9*(pitchCanSat+Ygyr[i]*(micros()-lastloop)/1000000)+0.1*180*atan2(-Xacc[i],sqrt(Yacc[i]*Yacc[i]+Zacc[i]*Zacc[i]))/3.14;
    lastloop=micros();
  }//Use those 10 to calculate pitchCanSat,rollCanSat
}

void calculateGyroValues(){
//  recordAccelRegisters();  //yhese are called in printData;
//  recordGyroRegisters();
  printData();
}

void setup() {
  rollCanSatOffset = 0;
  pitchCanSatOffset = 0;
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  mpuInIt();
}

void loop() {
  calculateGyroValues();
  Serial.print(rollCanSat-rollCanSatOffset);
  Serial.print("\t");
  Serial.println(pitchCanSat-pitchCanSatOffset);
  delay(900);
}
