#include <Wire.h>  //This is the library that is used for I2C communication
#include <TimerOne.h>   
#define SAMPLETIMEMICRO 100000         //10000 microsecond = 10 millisec
#define SAMPLETIMESEC 0.1 


long gyroX, gyroY, gyroZ;             //3 long : This will store the RAW data read from the gyro of the MPU itself
float rotX, rotY,rotZ;                //3 floats:This will be storing rotational speed or velocity around those axis

float gyroX_offset = 0;
float gyroY_offset = 0;
float gyroZ_offset = 0;

float rotationX = 0; //in degrees
float rotationY = 0; //in degrees
float rotationZ = 0; //in degrees



void setup() {
  Serial.begin(9600);       
            
  Wire.begin();         //-------->>>>//Command that we need to initialize our I2C communication
                                      //Abosultely a must before we start reading and writing any 
                                      //data from I2C enabled devices
                                      
  
  
  setupMPU();           //this is a function defined below

//  gyroX_offset = 0;
//  gyroY_offset = 0;
//  gyroZ_offset = 0;
  callibrateGyro();
  Serial.println("CALLIBRATION FINISHED");
  
//  After gyro is calibrated:
//  Timer1.initialize(100000);   //Initializing Software Interrupts
//  Timer1.attachInterrupt(findRotation);    //Attaching software interrupt
}

void loop() { 
  recordGyroRegisters();
  processGyroData();
  printRotationData();
}

//MAIN PURPOSE OF SETUP MPU FUNCTION IS:
//1.) To establish communnication with the MPU.
//2.) Setup up all the registers which we will be using in order to read data back from the MPU in the arduino 
void setupMPU(){
  //1. Implementaion of Power Manamegent Register
  Wire.beginTransmission(0b1101000);      //This is the I2C address of the MPU (b1101000/b1101001 for AD0 low/high datasheet sec. 9.2: I2C Interface)
  Wire.write(0x6B);                       //Accessing the register 6B (Decimal: 107) - Power Management (Sec. 4.28). This register deals with power management.
  Wire.write(0b00000000);                 //Setting SLEEP register to 0. (Required; see Note on p. 9). Seeing documentation, By setting reqd bits to 0, MPU is not in sleep mode or external clock mode. 
  Wire.endTransmission();  
  
  //2. Implementaion of Gyroscope Register
  Wire.beginTransmission(0b1101000);      //I2C address of the MPU
  Wire.write(0x1B);                       //Accessing the register 1B (Decimal: 27) - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000);                 //Setting the gyro to full scale +/- 250deg./s............ This range can be extended to +/-2000deg./s
  Wire.endTransmission(); 

  //3. Implementaion of Accelerometer Register
  Wire.beginTransmission(0b1101000);      //I2C address of the MPU
  Wire.write(0x1C);                       //Accessing the register 1C (Decimal: 28) - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000);                 //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000);      //I2C address of the MPU
  Wire.write(0x43);                       //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);          //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  
}

void processGyroData() {
  rotX = (gyroX-gyroX_offset) / 131.0;
  rotY = (gyroY-gyroY_offset) / 131.0; 
  rotZ = (gyroZ-gyroZ_offset) / 131.0;
}

void printRotationData() {
  Serial.print("X=");
  Serial.print(rotationX);
  Serial.print(" Y=");
  Serial.print(rotationY);
  Serial.print(" Z=");
  Serial.println(rotationZ);
}


void callibrateGyro(){
  Serial.print("CALLIBRATING GYRO");
   long SumOfDataX = 0;
   long SumOfDataY = 0;
   long SumOfDataZ = 0;
  
  for(int i=0; i<2000; i++){
    recordGyroRegisters();
    Serial.print(".");
//    printRawData();
    SumOfDataX +=  gyroX;
    SumOfDataY +=  gyroY;
    SumOfDataZ +=  gyroZ;

//    Serial.print(" SumX=");
//    Serial.print(SumOfDataX);
//    Serial.print(" SumY=");
//    Serial.print(SumOfDataY);
//    Serial.print(" SumZ=");
//    Serial.println(SumOfDataZ);
    
    delay(3);
  }

  gyroX_offset = SumOfDataX/2000;
  gyroY_offset = SumOfDataY/2000;
  gyroZ_offset = SumOfDataZ/2000;

  Serial.print(" OffX=");
  Serial.print(gyroX_offset);
  Serial.print(" OffY=");
  Serial.print(gyroY_offset);
  Serial.print(" OffZ=");
  Serial.println(gyroZ_offset);
  Serial.println("CALLIBRATION FINISHED");
}


//void findRotation(){
//  //Serial.println("f");
//  recordGyroRegisters();
//  processGyroData();
//  
//  rotationX += rotX*SAMPLETIMESEC;
//  rotationY += rotY*SAMPLETIMESEC;
//  rotationZ += rotZ*SAMPLETIMESEC;
//}

