int dPin = 3;   
volatile unsigned long count = 0;

int valPin = 2;int val = 0;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(dPin, INPUT);
  pinMode(valPin, INPUT);
  count = 0;           
  attachInterrupt(digitalPinToInterrupt(dPin), raiseCount, CHANGE); //Attaching the interrupts  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(count);
  val = digitalRead(valPin);
  int val2 = digitalRead(dPin);
  Serial.print("\t");
  Serial.print(val);
  
  Serial.print("\t");
  Serial.println(val2);
  delay(1000);
}

void raiseCount(){                             
  count++;
}

