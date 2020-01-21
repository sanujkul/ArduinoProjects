#include "MPU9250.h"

MPU9250 mpu;
double YawOffset = 0;
double Yaw = 0;
double YawCorrected = 0;
void setup()
{
    Serial.begin(115200);

    Wire.begin();

    delay(2000);
    mpu.setup();

    for(int i=0; i<10000; i++){
      updateYawValue();
    }
    YawOffset = Yaw;
}

void loop()
{
    updateYawValue();
//    YawCorrected = (Yaw - YawOffset);
//    Serial.println(YawCorrected);
}

void updateYawValue(){
  static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 16)
    {
        mpu.update();
//        mpu.print();

//        Serial.print("roll  (x-forward (north)) : ");
//        Serial.println(mpu.getRoll());
//        Serial.print("pitch (y-right (east))    : ");
//        Serial.println(mpu.getPitch());
//        Serial.print("yaw   (z-down (down))     : ");
//        Serial.print("\t");
//        Serial.println(mpu.getYaw());
        Yaw = mpu.getYaw();
        Serial.println(Yaw);
        prev_ms = millis();
    }
}
