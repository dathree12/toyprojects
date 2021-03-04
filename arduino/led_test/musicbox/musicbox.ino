// 부저에서 PWM 50% 대역에서 사용할 주파수 설정 (31~65535Hz)
// like 풀잎피리의 떨림을 통한 소리
// const int 상수 선언(자바에서의 static final int) 
const int c = 261, d = 294, e = 329, f = 349, g = 391;
const int gS = 415, a = 440, aS = 455, b = 466, cH = 523;
const int cSH = 554, dH = 587, dSH = 622, eH = 659, fH = 698;
const int fSH = 740, gH = 784, gSH = 830, aH = 880;
 
const int buzzerPin = 3;
const int ledPin1 = 12; // 빨간 LED
const int ledPin2 = 13; // 초록 LED

// LED를 번갈아 켜기 위한 변수
int counter = 0;

void setup()
{
  // 핀 설정하기
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}
 
void loop()
{  
  // 첫번째 파트 재생
  firstSection();
  // 두번째 파트 재생
  secondSection();
 
  // 중간 연결 부
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);
 
  delay(500);
 
  // 두번째 파트 재생
  secondSection();
 
  // 마무리 음악
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  
 
  delay(1000);
}

void beep(int note, int duration)
{
  // 부저로 소리를 재생하는 함수
  tone(buzzerPin, note, duration);
 
  //'counter' 변수에 따라 LED 깜빡이 변경
  if(counter % 2 == 0) {
    digitalWrite(ledPin1, HIGH);
    delay(duration);
    digitalWrite(ledPin1, LOW);
  } else {
    digitalWrite(ledPin2, HIGH);
    delay(duration);
    digitalWrite(ledPin2, LOW);
  }
 
  // 음악 재생 중지
  noTone(buzzerPin);
  delay(50);

  // counter 변수 증가
  counter++;
}

void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
 
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
}
 
void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  delay(325);
 
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  delay(350);
}
