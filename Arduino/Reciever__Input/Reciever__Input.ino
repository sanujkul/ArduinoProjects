#include <EnableInterrupt.h>
#include <Servo.h>  //Using servo library to control ESC

Servo esc1;          //Creating an object of Servo
Servo esc2;
Servo esc3;
Servo esc4;

#define SERIAL_PORT_SPEED 57600
#define RC_NUM_CHANNELS  4

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3

#define RC_CH1_INPUT  A0
#define RC_CH2_INPUT  A1
#define RC_CH3_INPUT  A2
#define RC_CH4_INPUT  A3

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];   //Read about volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope--qualifiers/volatile/
                                                // 16 bit = 2 byte unsigned integer

int channet4Output = 1000;

int esc1Pin = 8;
int esc2Pin = 9;
int esc3Pin = 10;
int esc4Pin = 11;

void rc_read_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_INPUT); }
void calc_ch3() { calc_input(RC_CH3, RC_CH3_INPUT); }
void calc_ch4() { calc_input(RC_CH4, RC_CH4_INPUT); }

void setup() {
  Serial.begin(SERIAL_PORT_SPEED);
  esc1.attach(esc1Pin);                //Specify ESC pin, here as D9
  esc2.attach(esc2Pin);
  esc3.attach(esc3Pin);
  esc4.attach(esc4Pin);
  
  esc1.write(1000);  //initialize the signal to 1000
  esc2.write(1000);
  esc3.write(1000);
  esc4.write(1000);

  pinMode(RC_CH1_INPUT, INPUT);
  pinMode(RC_CH2_INPUT, INPUT);
  pinMode(RC_CH3_INPUT, INPUT);
  pinMode(RC_CH4_INPUT, INPUT);

  enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_INPUT, calc_ch2, CHANGE);
  enableInterrupt(RC_CH3_INPUT, calc_ch3, CHANGE);
  enableInterrupt(RC_CH4_INPUT, calc_ch4, CHANGE);

  
}

void loop() {
  rc_read_values();

  Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]); Serial.print("\t");
  Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]); Serial.print("\t");
  Serial.print("CH3:"); Serial.print(rc_values[RC_CH3]); Serial.print("\t");
  Serial.print("CH4:"); Serial.println(rc_values[RC_CH4]);Serial.print("\t");

  channet4Output = map(rc_values[RC_CH3],1000,2000,1000,2000);
//
  Serial.print("\tMapped value");Serial.println(channet4Output);
  esc1.writeMicroseconds(channet4Output); 
  esc2.writeMicroseconds(channet4Output);
  esc3.writeMicroseconds(channet4Output);
  esc4.writeMicroseconds(channet4Output);
  
  delay(100);
}
