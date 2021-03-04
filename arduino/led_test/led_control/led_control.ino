/*
 * 아두이노 웹 서버 만들기 - part.1 -
 * 웹 서버에서 아두이노 센서 제어하기
 * 본 예제를 테스트하기 전에 
 * 파일 > 예제 > Ethernet > DhcpAddressPrinter 예제를 먼저 테스트 하여
 * 본인의 IP 주소를 확인 하시기 바랍니다.
 */
#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x03}; //mac 주소 입력

IPAddress ip(192,168,20,4);  // 로컬 네트워크에서 잡힌 IP Address

EthernetServer server(80); //80은 포트번호

#define RED_PORT 3     //RED rgb 핀
// #define GREEN_PORT 12   //GREEN rgb 핀
// #define BLUE_PORT 11    //BLUE rgb 핀

boolean statusLED = false;    // LED 상태
String buffer = "";       // 수신 데이터 버퍼

void setup() {
  Serial.begin(9600);
 
//이더넷 디바이스 초기화
  Ethernet.begin(mac, ip);

  Serial.println("WebServerControlLED");
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  //서버 연결 시작
  server.begin();
  
   delay(2000);        // 이더넷 쉴드의 초기화 대기
   
  pinMode(RED_PORT, OUTPUT);    //RED 핀 출력 설정
  digitalWrite(RED_PORT, LOW); //RED 핀 초기 설정으로 꺼놓기
  
}

void loop() {
  //수신 클라이언트가 있는 지 확인
  EthernetClient client = server.available();
  if (client) {         // 웹 브라우저가 접속한 경우
    int response_type = -1;
    Serial.println("** New client connected...");
    
    while (client.connected()) {
      // 줄 단위의 데이터 수신
      // HTML 요청의 끝을 알아내기 위해 빈 줄이 수신되었는지의 여부를 반환함
      boolean empty_line = read_one_line(client);
      Serial.println(buffer);
      if(buffer.indexOf("GET / ") >= 0)
        response_type = 1;    // 메인 페이지 요청
      else if(buffer.indexOf("GET /led.cgi?LEDstatus=1") >= 0)
        response_type = 2;    // LED ON 페이지 요청
      else if(buffer.indexOf("GET /led.cgi?LEDstatus=0") >= 0)
        response_type = 3;    // LED OFF 페이지 요청
      if(empty_line) break;   // HTML 요청이 끝나면 결과 전송
    }
    
    switch(response_type){    // 웹 브라우저의 요청에 따른 결과 전송
      case 1: 
        show_main_page(client);
        break;
      case 2: 
        show_on_off_page(client, true);
        break;
      case 3: 
        show_on_off_page(client, false);
        break;
    }

    client.stop();        // 웹 브라우저 연결 종료
    Serial.println("** Client disonnected...");
  }
}

boolean read_one_line(EthernetClient client)
{
  buffer = "";        // 버퍼 비움
  while(client.available()){
    char c = client.read();   // 바이트 데이터 읽기
    if(c == '\r'){        // 개행문자를 수신한 경우
      client.read();      // ‘\n’ 문자 버림
      break;
    }
    buffer = buffer + c;      // 개행문자 이외의 문자는 버퍼에 저장
  }

  return (buffer.length() == 0);    // 빈 줄 여부 반환
}

void show_main_page(EthernetClient client)
{
  // HTML 헤더
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();

  // HTML 내용
  client.println("<html>");
  client.println("<body><script>");

  // HTML 내용
  client.println("window.location.href = \"http://192.168.120.3:8088/testArduino/\";");
  client.print("alert('Currently... LED is "); // 현태 LED 상태 표시
  client.println(statusLED ? "ON.');" : "OFF.');");
    
  client.println("</script></body>");
  client.println("</html>");
}

void show_on_off_page(EthernetClient client, boolean status)
{
  statusLED = status;     // LED 상태 저장
  digitalWrite(RED_PORT, status);   // LED 상태 바꿈
  String str = "LED 상태 : ";
  Serial.println(str + (status ? "HIGH" : "LOW"));
  
  // HTML 헤더
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();

  // HTML 내용
  client.println("<html>");
  client.println("<body><script>");
  client.println("window.location.href = \"http://192.168.120.3:8088/testArduino/\";");
  client.print("alert('Currently... LED is "); // 현태 LED 상태 표시
  client.println(statusLED ? "ON.');" : "OFF.');");
  
  client.println("</script></body>");
  client.println("</html>");
}
