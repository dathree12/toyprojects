const int PIRPin = 2; //디지털 핀
const int ledPin= 13; //디지털 핀

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(PIRPin, INPUT);

  Serial.begin(9600); //print Serial interval

}

void loop() {
  int value1 = digitalRead(PIRPin);
  Serial.println(value1); //시리얼 값 확인

  if (value1 == HIGH) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, LOW);
  }

}
