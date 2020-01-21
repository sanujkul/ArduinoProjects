#define RC_NUM_CHANNELS  5
int PWM[RC_NUM_CHANNELS];
//Following are indexes are for above Array:
#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3
#define RC_CH5  4 
#define RC_CH6  5

int motorOrARM = 0;  //0 FOR MOTOR AND 1 FOR ARM

////////// VARIABLES FOR IBT2 //////////////////////
//Left front
#define RPWM_PIN_FRONT_LEFT 8 // Arduino PWM output pin 6; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_FRONT_LEFT 9 // Arduino PWM output pin 2; connect to IBT-2 pin 2 (LPWM)
//Right Front
#define RPWM_PIN_FRONT_RIGHT 12 // Arduino PWM output pin 9; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_FRONT_RIGHT 13 // Arduino PWM output pin 5; connect to IBT-2 pin 2 (LPWM)

//Left Rear
#define RPWM_PIN_REAR_LEFT 10 // Arduino PWM output pin 6; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_REAR_LEFT 11 // Arduino PWM output pin 2; connect to IBT-2 pin 2 (LPWM)
//Right Rear
#define RPWM_PIN_REAR_RIGHT 44 // Arduino PWM output pin 9; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_REAR_RIGHT 45 // Arduino PWM output pin 5; connect to IBT-2 pin 2 (LPWM)

///////////////// Direction of DRIVING //////////////////////////////////////////////
#define FORWARD 0
#define BACKWARD 1

#define LEFT 0
#define RIGHT 1
int driveDirFB = -1;  //This is direction if rover is moving FORWARD or BACKWARD
int driveDirRL = -1;  //This is direction if rover is moving RIGHT or LEFT


////////////////////////////////////////////////////////////////////////////////
///////////////////SET UP and LOOP///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  setupIBT2Pins();
}

void loop() {
  String data = Serial.readString();
  Serial.println(data);
  
  storeDataInVariables(data);
  
  
  
  
  
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////// HELPING FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
 * Function : storeDataInVariables
 * Role     : To store variables in PWM[] and motorOrARM
 */
boolean storeDataInVariables(String text){
  int posl = 0;
  int posr = text.indexOf(",");
  //We will check if posr exist or not.It is does not exist then nothing was saved in backup files
  if(posr < 0){
    return false;
  }
  String data = text.substring(posl,posr);
  motorOrARM = data.toInt();

  //Now storing values in PWM[RC_NUM_CHANNELS]
  for(int i=RC_CH1; i<=RC_CH5;i++){
    //Second Field is ground altitude from bmp:
    posl = posr+1;
    posr = text.indexOf(",",posl);
    if(posr == -1) return false;

    data = text.substring(posl,posr);
    PWM[i] = data.toInt();
  }
  
  int lastPos = text.lastIndexOf(",");
  data = text.substring(lastPos+1);
  PWM[RC_CH6] = data.toInt();

  return true;
}

/*
 * Function : setupIBT2Pins
 * Role     : To set all pins used for IBT2 as OUTPUT
 * 
 */
void setupIBT2Pins(){
  pinMode(RPWM_PIN_FRONT_LE1FT, OUTPUT);
  pinMode(LPWM_PIN_FRONT_LEFT, OUTPUT);
  
  pinMode(RPWM_PIN_FRONT_RIGHT, OUTPUT);
  pinMode(LPWM_PIN_FRONT_RIGHT, OUTPUT);

  pinMode(RPWM_PIN_REAR_LEFT, OUTPUT);
  pinMode(LPWM_PIN_REAR_LEFT, OUTPUT);
  
  pinMode(RPWM_PIN_REAR_RIGHT, OUTPUT);
  pinMode(LPWM_PIN_REAR_RIGHT, OUTPUT);
}

/*
 * Function : DRINVING FUNCTIONS
 * Role     : FRONT, BACK, LEFT, RIGHT Functions for MEGA
 */
void driveForward(int pwmSignal1, int pwmSignal2, int pwmSignal3, int pwmSignal4){
  
  analogWrite(RPWM_PIN_FRONT_LEFT, pwmSignal1);
  analogWrite(LPWM_PIN_FRONT_LEFT, 0);

  analogWrite(RPWM_PIN_FRONT_RIGHT, pwmSignal2);
  analogWrite(LPWM_PIN_FRONT_RIGHT, 0);

  analogWrite(RPWM_PIN_REAR_LEFT, pwmSignal3);
  analogWrite(LPWM_PIN_REAR_LEFT, 0);

  analogWrite(RPWM_PIN_REAR_RIGHT, pwmSignal4);
  analogWrite(LPWM_PIN_REAR_RIGHT, 0);
}

void driveBackward(int pwmSignal1, int pwmSignal2, int pwmSignal3, int pwmSignal4){
  
  analogWrite(RPWM_PIN_FRONT_LEFT, 0);
  analogWrite(LPWM_PIN_FRONT_LEFT, pwmSignal1);

  analogWrite(RPWM_PIN_FRONT_RIGHT, 0);
  analogWrite(LPWM_PIN_FRONT_RIGHT, pwmSignal2);

  analogWrite(RPWM_PIN_REAR_LEFT, 0);
  analogWrite(LPWM_PIN_REAR_LEFT, pwmSignal3);

  analogWrite(RPWM_PIN_REAR_RIGHT, 0);
  analogWrite(LPWM_PIN_REAR_RIGHT, pwmSignal4);
}

void driveRight(int pwmSignal1, int pwmSignal2, int pwmSignal3, int pwmSignal4){
  analogWrite(RPWM_PIN_FRONT_LEFT, pwmSignal1);
  analogWrite(LPWM_PIN_FRONT_LEFT, 0);

  analogWrite(RPWM_PIN_FRONT_RIGHT, 0);
  analogWrite(LPWM_PIN_FRONT_RIGHT, pwmSignal2);

  analogWrite(RPWM_PIN_REAR_LEFT, pwmSignal3);
  analogWrite(LPWM_PIN_REAR_LEFT, 0);

  analogWrite(RPWM_PIN_REAR_RIGHT, 0);
  analogWrite(LPWM_PIN_REAR_RIGHT, pwmSignal4);
}

void driveLeft(int pwmSignal1, int pwmSignal2, int pwmSignal3, int pwmSignal4){
  analogWrite(RPWM_PIN_FRONT_LEFT, 0);
  analogWrite(LPWM_PIN_FRONT_LEFT, pwmSignal1);

  analogWrite(RPWM_PIN_FRONT_RIGHT, pwmSignal2);
  analogWrite(LPWM_PIN_FRONT_RIGHT, 0);

  analogWrite(RPWM_PIN_REAR_LEFT, 0);
  analogWrite(LPWM_PIN_REAR_LEFT, pwmSignal3);

  analogWrite(RPWM_PIN_REAR_RIGHT, pwmSignal4);
  analogWrite(LPWM_PIN_REAR_RIGHT, 0);
}

void stop(){
  analogWrite(RPWM_PIN_FRONT_LEFT, 0);
  analogWrite(LPWM_PIN_FRONT_LEFT, 0);

  analogWrite(RPWM_PIN_FRONT_RIGHT, 0);
  analogWrite(LPWM_PIN_FRONT_RIGHT, 0);

  analogWrite(RPWM_PIN_REAR_LEFT, 0);
  analogWrite(LPWM_PIN_REAR_LEFT, 0);

  analogWrite(RPWM_PIN_REAR_RIGHT, 0);
  analogWrite(LPWM_PIN_REAR_RIGHT, 0);
}

//////////////////// MAIN DRIVER FUNCTION //////////////////
void drive2(int forBackWardChannel, int leftRightChannel){
  int motorSpeedLeft_Forward = 0;
  int motorSpeedRight_Forward = 0;

  int motorSpeedLeft_Backward = 0;
  int motorSpeedRight_Backward = 0;
  
  int driveDir = -1;                                      //0--> Forward, 1 ---> Backward

  //In this if/else i am setting if we are going forward and backward
  if(PWM[forBackWardChannel] >= 10){                  //Drive Forward
     driveDirFB = FORWARD;
  }else if(PWM[forBackWardChannel] < -10){           //Drive Backward
     driveDirFB = BACKWARD;
  }else{
    driveDirFB = -1;
  }

  if(PWM[leftRightChannel] >= 20){                  //Drive Forward
     driveDirLR = RIGHT;
  }else if(PWM[forBackWardChannel] < -10){           //Drive Backward
     driveDirLR = LEFT;
  }else{
    driveDirLR = -1;
  }
  Serial.println("drivedirFB = "+drivedirFB);

  

}
