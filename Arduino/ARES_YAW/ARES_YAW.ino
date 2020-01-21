/*
Basic_I2C.ino
Brian R Taylor
brian.taylor@bolderflight.com
Copyright (c) 2017 Bolder Flight Systems
Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <MPU9250.h>
//#include <ros.h>
//#include "sensor_msgs/Imu.h"
//#include <ros/time.h>
//ros::NodeHandle nh;
//#include <ArduinoJson.h>

//doc["time"] = 1351824120;




#define GYRO_SENSITIVITY_2000DPS          (0.070F)
#define SENSORS_GRAVITY_EARTH             (9.80665F)              /**< Earth's gravity in m/s^2 */
#define SENSORS_GRAVITY_STANDARD          (SENSORS_GRAVITY_EARTH)
#define SENSORS_DPS_TO_RADS               (0.017453293F)          /**< Degrees/s to rad/s multiplier */
#define SENSORS_MILIGAUSS_TO_TESLA        (10000000)


// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
//int count;

void setup() {
  // serial to display data
  Serial.begin(57600);
  while(!Serial) {}

  // start communication with IMU 
  int status;
  status = IMU.begin();
//  count = 1;
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
}

void loop() {
  // read the sensor
//  sensor_msgs::Imu imu;
//  ros::Publisher chatter("chatter", &imu);
StaticJsonDocument<200> imu;
  IMU.readSensor();
    

//  if (count == 1) {
//    nh.initNode();
//    nh.advertise(chatter);
//  }
//  count++;
//  // display the data
//  Serial.print(IMU.getAccelX_mss(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getAccelY_mss(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getAccelZ_mss(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getGyroX_rads(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getGyroY_rads(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getGyroZ_rads(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getMagX_uT(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getMagY_uT(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getMagZ_uT(),6);
//  Serial.print("\t");
//  Serial.println(IMU.getTemperature_C(),6);
//  imu.header.stamp = nh.now();
//  imu.header.frame_id = "imu_link";

//  imu.orientation_covariance[0] = 0.0025;
//  imu.orientation_covariance[1] = 0;
//  imu.orientation_covariance[2] = 0;
//  imu.orientation_covariance[3] = 0;
//  imu.orientation_covariance[4] = 0.0025;
//  imu.orientation_covariance[5] = 0;
//  imu.orientation_covariance[6] = 0;
//  imu.orientation_covariance[7] = 0;
//  imu.orientation_covariance[8] = 0.0025;
//
//  imu.angular_velocity_covariance[0] = 0.0025;
//  imu.angular_velocity_covariance[1] = 0;
//  imu.angular_velocity_covariance[2] = 0;
//  imu.angular_velocity_covariance[3] = 0;
//  imu.angular_velocity_covariance[4] = 0.0025;
//  imu.angular_velocity_covariance[5] = 0;
//  imu.angular_velocity_covariance[6] = 0;
//  imu.angular_velocity_covariance[7] = 0;
//  imu.angular_velocity_covariance[8] = 0.0025;
//  
//  imu.linear_acceleration_covariance[0] = 0.0025;
//  imu.linear_acceleration_covariance[1] = 0;
//  imu.linear_acceleration_covariance[2] = 0;
//  imu.linear_acceleration_covariance[3] = 0;
//  imu.linear_acceleration_covariance[4] = 0.0025;
//  imu.linear_acceleration_covariance[5] = 0;
//  imu.linear_acceleration_covariance[6] = 0;
//  imu.linear_acceleration_covariance[7] = 0;
//  imu.linear_acceleration_covariance[8] = 0.0025;
  

  float roll = (float)atan2(IMU.getAccelY_mss(), IMU.getAccelZ_mss());
//  imu.orientation.x = roll;
  float pitch;
  if (IMU.getAccelY_mss() * sin(roll) + IMU.getAccelZ_mss() * cos(roll)==0){
    if (IMU.getAccelX_mss()>0){
      pitch = 3.14159265F / 2;
    } else{
      pitch = -3.14159265F / 2;
    }
  }else{
    pitch = (float)atan(-IMU.getAccelX_mss() / (IMU.getAccelY_mss() * sin(roll) + IMU.getAccelZ_mss() * cos(roll)));
  }

  imu["orientationy"] = pitch;

  float yaw = (float)atan2(IMU.getMagZ_uT() * sin(roll) - IMU.getMagY_uT() * cos(roll), IMU.getMagX_uT() * cos(pitch) + IMU.getMagY_uT() * sin(pitch) * sin(roll) + IMU.getMagZ_uT() * sin(pitch) * cos(roll));
//  float roll = (float)atan2(-IMU.getAccelX_mss(), (sqrt(IMU.getAccelY_mss() * IMU.getAccelY_mss()))
  imu["orientationz"] = yaw;

  imu["orientationw"] = 1;

  imu["angular_velocityx"] = IMU.getGyroX_rads() * GYRO_SENSITIVITY_2000DPS * SENSORS_DPS_TO_RADS;
  imu["angular_velocityy"] = IMU.getGyroY_rads() * GYRO_SENSITIVITY_2000DPS * SENSORS_DPS_TO_RADS;
  imu["angular_velocityz"] = IMU.getGyroZ_rads() * GYRO_SENSITIVITY_2000DPS * SENSORS_DPS_TO_RADS;
//
  imu["linear_accelerationx"]= IMU.getAccelX_mss() * SENSORS_GRAVITY_STANDARD;
  imu["linear_accelerationy"] = IMU.getAccelY_mss() * SENSORS_GRAVITY_STANDARD;
  imu["linear_accelerationz"] = IMU.getAccelZ_mss() * SENSORS_GRAVITY_STANDARD;

//  if (nh.connected()) {
//    Serial.print("connected");
//  }
//  chatter.publish( &imu );

//  nh.spinOnce();
serializeJson(imu, Serial);
Serial.print("\n");
  delay(100);
}
