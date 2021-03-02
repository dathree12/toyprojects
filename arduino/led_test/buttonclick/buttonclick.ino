int redLED = 2; //LED 핀 설정
int sw = 8; //스위치 핀 설정

void setup() {
  pinMode(redLED,OUTPUT); //LED 핀 연결
  pinMode(sw, INPUT_PULLUP); //스위치 핀 연결
  // ** INPUT_PULLUP으로 눌렀을 때 INPUT이 되도록 연결한다.
}

void loop() {
  // digitalRead(핀)로 사용자가 눌느 스위치의 값을 가져올수 있다.
  // 스위치가 눌리면 'LOW' / 스위치가 떨어지면 'HIGH'

  if(digitalRead(sw) == LOW) { //스위치를 눌렀다면
    digitalWrite(redLED, HIGH); //LED 불 켜기
  } else {                      // 스위치에서 손을 떼었다면
    digitalWrite(redLED, LOW); //LED 불끄기
  }

}
