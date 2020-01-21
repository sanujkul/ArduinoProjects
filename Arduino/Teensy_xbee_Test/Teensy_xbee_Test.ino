#define xbee Serial1
#define XBEE_INTERRUPT_PIN 2    //Connect RSSI pin of XBEE to pin 2 of Teensy
int count = 0;

void setup() {
  // put your setup code here, to run once:
  xbee.begin(9600);
  //Setting Interrupt at pin 2
  pinMode(XBEE_INTERRUPT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(XBEE_INTERRUPT_PIN), xbeeMessegeReceived, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
//  xbee.println("Hello ");
  Serial.print(count);
  Serial.print(" ");
  Serial.println(digitalRead(XBEE_INTERRUPT_PIN));
  delay(1000);
}

void xbeeMessegeReceived(){
//  detachInterrupt(digitalPinToInterrupt(XBEE_INTERRUPT_PIN));
//  if(digitalRead(XBEE_INTERRUPT_PIN) == 1)
    count++;
    int x = xbee.parseInt();
//    while(digitalRead(XBEE_INTERRUPT_PIN) != 0){/*Do Nothing unless pin goes low*/}
    Serial.println(x);
}

