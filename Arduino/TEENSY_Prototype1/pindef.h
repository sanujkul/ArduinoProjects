#include <MPU6050_tockn.h>
#include <RTClib.h>    //RTC Library
#include <Arduino.h>   // required before wiring_private.h
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include <Adafruit_BMP280.h> //BMP Library
#include "packet.h"

#define voltagePin A8

#define gps_uart Serial2
#define zigbee Serial1
#define SD_SELECT 10

#define LOG_MISSION	//enable this to log mission events to SD card
#define SER_DEBUG		//enable this to get debug info in serial monitor
#define TEAM_ID 3279		//TEAM KALAM
