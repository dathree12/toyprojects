int buzzerPin = 3; // 피에조 부저 핀 선언

void setup() {
pinMode(buzzerPin, OUTPUT); //피에조 부저 핀 선언
}

void loop() {
  //피에조 부저는 PWM(펄스 폭 진동 : 0 ~255)을 통하여
  //소리를 내기 때문에 ~표시가 있는 디지털 핀 번호를 사용해야함

  analogWrite(buzzerPin, 32); //PWM 25% 적용
  delay(1000);

  analogWrite(buzzerPin, 64); //PWM 25% 적용
  delay(1000);

  analogWrite(buzzerPin, 128); //PWM 25% 적용
  delay(1000);

}
