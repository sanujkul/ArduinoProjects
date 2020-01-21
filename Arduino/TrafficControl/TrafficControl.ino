
int R1 = 0;
int G1 = 1;

int R2 = 2;
int G2 = 3;

int R3 = 4;
int G3 = 5;

int values[6];

int currTime = 0;

void setup() {
  // put your setup code here, to run once:
 
}

void loop() {
  // put your main code here, to run repeatedly:

  currTime  = (millis()/1000)%60;

  if(currTime<20){
    traffic1();
  }
  else if(currTime>=20 && currTime<40){
    traffic2();
  }else{
    traffic3();
  }

  
  

}

//Each of following function will return start time of that function:

void traffic1(){
  int start = millis();
  values[1] = 1;
  values[2] = 1;
  values[4] = 1;

  values[0] = 0;
  values[3] = 0;
  values[5] = 0;

  return start;
}

void traffic2(){
  int start = millis();
  values[0] = 1;
  values[3] = 1;
  values[4] = 1;

  values[1] = 0;
  values[2] = 0;
  values[5] = 0;

  return start;
}

void traffic3(){
  int start = millis();
  values[0] = 1;
  values[2] = 1;
  values[5] = 1;

  values[1] = 0;
  values[3] = 0;
  values[4] = 0;

  return start;
}



