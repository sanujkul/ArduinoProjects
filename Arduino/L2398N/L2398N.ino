
//FOR BOTH RIGHT WHEELS:
#define enR 9        //enable right pin
#define inR1 4
#define inR2 5

//FOR BOTH LEDT WHEELS:
#define enL 10        //enable left pin
#define inL1 6
#define inL2 7

int motorSpeedR = 0;   //Speed of Right motor
int motorSpeedL = 0;   //Speed of Left motor


void setup() {
  //Enable pins
  pinMode(enR, OUTPUT);     
  pinMode(enL, OUTPUT);
  
  //Right pins direction control
  pinMode(inR1, OUTPUT);
  pinMode(inR2, OUTPUT);
  
  //Right pins direction control
  pinMode(inL1, OUTPUT);
  pinMode(inL2, OUTPUT);
}

void loop() {
  

}
