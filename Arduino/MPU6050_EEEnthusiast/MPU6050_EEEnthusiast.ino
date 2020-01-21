#include <Wire.h>  //This is the library that is used for I2C communication

signed int accelX, accelY, accelZ;          //3 long : This will store the RAW data read from the accelerometer MPU itself
float gForceX, gForceY, gForceZ;      //3 floats:This will be used to calculate g-force acting in three direction

signed int gyroX, gyroY, gyroZ;             //3 long : This will store the RAW data read from the gyro of the MPU itself
float rotX, rotY,rotZ;                //3 floats:This will be storing rotational speed or velocity around those axis


//#define Serial SerialUSB

void setup() {
  Serial.begin(9600);    
  while (!Serial) ; // Wait for Serial monitor to open   
  Serial.println("Started");          
  Wire.begin();         //-------->>>>//Command that we need to initialize our I2C communication
                                      //Abosultely a must before we start reading and writing any 
                                      //data from I2C enabled devices
  
  setupMPU();           //this is a function defined below
}

void loop() {
  recordAccelRegisters();
  recordGyroRegisters();

  
  
  printData();

  double AxelOffsetZSum = 0;
  for(int i=0; i<1000; i++){
    AxelOffsetZSum += (gForceZ-1);
  }
  AxelOffsetZSum /= 1000;
  Serial.println(16384*AxelOffsetZSum);
  
  delay(300);
}

//MAIN PURPOSE OF SETUP MPU FUNCTION IS:
//1.) To establish communnication with the MPU.
//2.) Setup up all the registers which we will be using in order to read data back from the MPU in the arduino 
void setupMPU(){
//  Serial.println("In SetUpMPU");     
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
  Serial.println("SetUpMPU finished");     

}

void recordAccelRegisters() {
//  Serial.println("recordAccelData");     
  Wire.beginTransmission(0b1101000);      //I2C address of the MPU............. Same used in setupMPU.
  Wire.write(0x3B);                       //Starting register for Accelerometer Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);          //Request Accelerometer Registers (3B to 40) i.e. from 6 registers
//  Serial.println("requestAccelData");
  while(Wire.available() < 6);            //Wire.available(): returns The number of bytes available for reading.
//  Serial.print("Wire.available() - Accelerometer : ");
//  Serial.println(Wire.available());
//  Serial.println("AccelData Available");
  //C CODE: leftShift and or operator
  //In documentation each coressponds to 2 bytes. 1 byte = 8 byte.
  //Wire.read() gives 1 byte (8 bit) at a time and then every time we use it, it shift to next bit.
  accelX = Wire.read()<<8|Wire.read();    //Store first two bytes into accelX     //Multiply highByte by 256 and ad lowByte
  accelY = Wire.read()<<8|Wire.read();    //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read();    //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = accelX / 16384.0;           //As we have selected full scale range 2g, LSB Sensitivity = 16384 LSB/g
  gForceY = accelY / 16384.0;           //Therefore for example our MPU reads 20,000 then it is = 20,000/16384 g = 1.22 g 
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() {
//    Serial.println("recordGyroData");     

  Wire.beginTransmission(0b1101000);      //I2C address of the MPU
  Wire.write(0x43);                       //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);          //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  Serial.print("Gyro (Raw/s)");
  Serial.print(" X=");
  Serial.print(gyroX);
  Serial.print(" Y=");
  Serial.print(gyroY);
  Serial.print(" Z=");
  Serial.println(gyroZ);
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printData() {
//    Serial.println("print Data");     

  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.print(gForceZ);
  
  float rollAngle = atan2 (gForceX,gForceZ)*180/3.14;  // arc tangent of Gx/Gz
  float pitchAngle = atan2 (gForceY,sqrt ((gForceX*gForceX) +(gForceZ*gForceZ)))*180/3.14;  // arc tangent of Gy/Sqrt(Gx^2 + Gy^2)
  
  Serial.print("\tRoll Angle = ");
  Serial.print(rollAngle);
  Serial.print(" \t Pitch Angle = ");
  Serial.println(pitchAngle);
}
