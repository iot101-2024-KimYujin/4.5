#include <Arduino.h>
#include <TFT_eSPI.h>
#include <DHTesp.h>

TFT_eSPI tft = TFT_eSPI();  // TFT 초기화
DHTesp dht;

// DHT22 데이터 관련 변수
int interval = 2000;
unsigned long lastDHTReadMillis = 0;
float humidity = 0;
float temperature = 0;

void setup() {
  // 시리얼 통신과 DHT22 초기화
  Serial.begin(115200);
  dht.setup(18, DHTesp::DHT22);
  delay(2000);
  // TFT 화면 초기화
  tft.init();
  tft.setRotation(1);  // 화면 회전
  tft.fillScreen(TFT_BLACK);  // 배경을 검은색으로 설정
  tft.setTextColor(TFT_WHITE);  // 텍스트 색상 설정
  tft.setTextSize(2);  // 텍스트 크기 설정
  
 
  Serial.println(); 
  Serial.println("Humidity (%)\tTemperature(C)");
}

// DHT22 센서 데이터 읽기 함수
void readDHT22() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastDHTReadMillis >= interval) {
    lastDHTReadMillis = currentMillis;
    
    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
    
  }
}


void loop() {
  // DHT22 센서에서 데이터를 읽고 TFT에 출력
  readDHT22();
  Serial.print(temperature);
  Serial.print("\t");
  Serial.println(humidity);

  tft.fillScreen(TFT_BLACK);  // 이전 데이터를 지우고 새로 출력

  tft.println("Temperature:");
  tft.printf("%.1f C\n", temperature);
  tft.setCursor(0,30);
  tft.println("Humidity:");
  tft.printf("%.1f %%\n", humidity);
  tft.setCursor(0,60);
  
  delay(2000);
}
