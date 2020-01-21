#define EncoderPin 9
int dPin = 2;
int count = 0;
void setup() {
  Serial.begin(9600);
  pinMode(EncoderPin, INPUT);
  count = 0;
  attachInterrupt(digitalPinToInterrupt(dPin), raiseCount, RISING); //Attaching the interrupts
}

void loop() {
//  int val = digitalRead(EncoderPin);
//  Serial.println(val);
  Serial.println(count);
}

void raiseCount(){                             
  count++;
}
