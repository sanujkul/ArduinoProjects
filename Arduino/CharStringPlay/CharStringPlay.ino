void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  String s = iNeedString();
  Serial.println(s);
}

String iNeedString(){
  char* sz = "Hello World";
  *sz += " I am here!";
  String s(sz);
  return s; 
}

