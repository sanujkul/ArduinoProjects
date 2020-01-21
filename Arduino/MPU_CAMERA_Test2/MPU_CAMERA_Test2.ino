#include <AutoPID.h>
#include <Servo.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <MadgwickAHRS.h>

#define MPU_READ_DELAY 200

Madgwick filter;
MPU6050 mpu6050(Wire);
float ax, ay, az;
float gx, gy, gz;
float roll, pitch;
double yaw_val, reference, servo_speed;
unsigned long lastMPUUpdate;
int temp;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
//  myservo.attach(9);
  filter.begin(50);
  update_yaw();
}

void loop() {
  // put your main code here, to run repeatedly:
  mpu6050.update();
  update_yaw();
  
  
}

void update_yaw() {
//  if ((micros() - lastMPUUpdate) > MPU_READ_DELAY) {
//    mpu6050.update();
//    ax = mpu6050.getAccX();
//    ay = mpu6050.getAccY();
//    az = mpu6050.getAccZ();
//    gx = mpu6050.getGyroX();
//    gy = mpu6050.getGyroY();
//    gz = mpu6050.getGyroZ();
//    filter.updateIMU(gx, gy, gz, ax, ay, az);
//    yaw_val = filter.getYaw();
//    lastMPUUpdate = micros();
//  }

    ax = mpu6050.getAccX();
    ay = mpu6050.getAccY();
    az = mpu6050.getAccZ();
    gx = mpu6050.getGyroX();
    gy = mpu6050.getGyroY();
    gz = mpu6050.getGyroZ();
    filter.updateIMU(gx, gy, gz, ax, ay, az);
    yaw_val = filter.getYaw();
    Serial.print(yaw_val);
    Serial.print("\t");
    Serial.println(mpu6050.getAngleZ());
}
