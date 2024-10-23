long TR;
long threshold = 100000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(48, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  TR = touchRead(8);
  Serial.println(TR);
  if (TR > threshold){
    digitalWrite(48, HIGH);
    Serial.println("High");
  }
  else {
    digitalWrite(48, LOW);
    Serial.println("Low");
  }
  delay(100);
}
