#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(6000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int badPoint = 1.8 * t - 0.55 *((1-(h/100))*((1.8-t)-26)+32); 
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" C");
  Serial.print("%\n");
  Serial.print("불쾌지수는 : ");
  Serial.print(badPoint);
  Serial.print(" 입니다.");
  Serial.print("%\n");

  if(badPoint < 68) {
    Serial.print("단계는 낮음입니다.(전원 쾌적함을 느낌)");
    Serial.print("%\n");
  } else if(badPoint >= 68 && badPoint < 75) {
    Serial.print("단계는 보통입니다.(50% 정도 불쾌함을 느낌)");
    Serial.print("%\n");
  } else if(badPoint >= 75 && badPoint < 80) {
    Serial.print("단계는 높음입니다.(불쾌감을 나타내기 시작함)");
    Serial.print("%\n");
  } else {
    Serial.print("단계는 매우높음입니다.(전원불쾌감을 느낌)");
    Serial.print("%\n");
  }








  
}
