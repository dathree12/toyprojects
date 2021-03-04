/*
 * 아두이노 웹 서버 만들기 - part.2 -
 * 아두이노 & AJAX
 * json 라이브러리 추가하기 :
 *  https://github.com/bblanchon/ArduinoJson
 *  설명 ) https://arduinojson.org/v6/api/
 * 라이브러리 관리에서 JSON 검색 후 ArduinoJSON by Benoit Blanchon 버전으로 받기
 * 본 예제를 테스트하기 전에 
 * 파일 > 예제 > Ethernet > DhcpAddressPrinter 예제를 먼저 테스트 하여
 * 본인의 IP 주소를 확인 하시기 바랍니다.
 * 
 * MIT license
 */
#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <ArduinoJson.h>
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x03}; //mac 주소 입력

IPAddress ip(192,168,20,4);  // 로컬 네트워크에서 잡힌 IP Address

EthernetServer server(80); //80은 포트번호
String buffer = "";       // 수신 데이터 버퍼

void setup() {
  Serial.begin(9600);
  
  //이더넷 디바이스 초기화
  Ethernet.begin(mac, ip);

  Serial.println("WebServer Send DHT11 Sensor DATA");
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  //서버 연결 시작
  server.begin();
  dht.begin();
  
  delay(2000);        // 이더넷 쉴드의 초기화 대기
}
void loop() {
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" C");
 
  //수신 클라이언트가 있는지 확인
  EthernetClient client = server.available();
  
  // 클라이언트가 없다면
  if (!client) return;
  else {   // 웹 브라우저가 접속한 경우
    Serial.println("** New client connected...");
    
      // Read the request (we ignore the content in this example)
      while (client.available()) client.read();
    
      // Allocate a temporary JsonDocument
      // Use arduinojson.org/v6/assistant to compute the capacity.
      DynamicJsonDocument doc(500);
    
      // Create the "analog" array
      doc["Humidity"] = dht.readHumidity();
      doc["Temperature"] = dht.readTemperature();
    
      Serial.print(F("Sending: "));
      serializeJson(doc, Serial);
      Serial.println();
    
      // Write response headers
      
      client.println(F("HTTP/1.0 200 OK"));
      // json으로 contentType 설정
      client.println(F("Content-Type: application/json; charset=utf-8"));
      client.println(F("Connection: close"));
      client.print(F("Content-Length: "));
      client.println(measureJsonPretty(doc));
      client.println();

      // json을 담을 임시 변수 설정
      String str = "";
      // doc에 담긴 json 데이터를 문자열로 변환
      // 일반 DynamicJsonDocument 객체로는 문자열 혼합이 불가능하다.
      serializeJson(doc, str);

      // 서버에 전달할 객체의 이름인 callback을 붙여 서버에 전송
      Serial.println("callback("+str+")");
      client.println("callback("+str+")");

    client.stop();        // 웹 브라우저 연결 종료
    Serial.println("** Client disonnected...");
  }
}
