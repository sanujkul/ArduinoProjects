void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print('S');
  delayMicroseconds(1500);
}
