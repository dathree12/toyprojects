int red = 6; //핀 설정
int blue = 8;
int green = 11;

void setup() { //핀선언
 pinMode(red, OUTPUT);
 pinMode(blue, OUTPUT);
 pinMode(green, OUTPUT);

}

void loop() {
  changeLights();
  delay(15000); // 각 반복마다 15초 씩 딜레이

}

void changeLights() {
  //초록색 LED OFF, 파란색 LED ON
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
  delay(3000);

  //파란색 LED OFF, 빨간색 LED ON
  digitalWrite(blue, LOW);
  digitalWrite(red, HIGH);
  delay(5000);

  //파란색 LED ON
  digitalWrite(blue, HIGH);
  delay(2000);

  //파란색 LED OFF, 빨간색 LED OFF
  digitalWrite(blue, LOW);
  digitalWrite(red, LOW);

  //초록색 LED ON
  digitalWrite(green, HIGH);







}
