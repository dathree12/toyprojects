int redLED = 6; //핀설정

void setup() {
  pinMode(redLED, OUTPUT); //핀테스트
}

void loop() {
  //LED ON / OFF : HIGH /LOW
  digitalWrite(redLED, HIGH);
  delay(1500); //1.5초 지속

  digitalWrite(redLED, LOW);
  delay(1500); //1.5초 지속

}
