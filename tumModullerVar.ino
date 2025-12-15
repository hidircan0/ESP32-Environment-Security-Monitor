#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===== OLED =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ===== DHT11 =====
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ===== Sensörler =====
#define LDR_AO 36
#define PIR_PIN 27
#define OBS_PIN 26

// ===== Çıkışlar =====
#define PASSIVE_BUZZER 18
#define ACTIVE_BUZZER 19
#define RELAY1 25

int previousMode = -1;

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(OBS_PIN, INPUT);

  pinMode(PASSIVE_BUZZER, OUTPUT);
  pinMode(ACTIVE_BUZZER, OUTPUT);
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, HIGH);

  dht.begin();

  // ===== OLED INIT =====
  Wire.begin(21,22);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED bulunamadi");
    while(true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void passiveBeep(int mode) {
  int freq = 400;
  if(mode == 0) freq = 200;
  else if(mode == 1) freq = 500;
  else if(mode == 2) freq = 900;
  else if(mode == 3) freq = 1400;
  tone(PASSIVE_BUZZER, freq, 200);
}

void activeAlarm(bool alarm) {
  digitalWrite(ACTIVE_BUZZER, alarm ? HIGH : LOW);
}

String modeName(int mode){
  if(mode==0) return "UYKU";
  if(mode==1) return "NORMAL";
  if(mode==2) return "STRES";
  return "TEHDIT";
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();
  int light = analogRead(LDR_AO);
  bool motion = digitalRead(PIR_PIN);
  bool obstacle = digitalRead(OBS_PIN);

  int mode = 1;
  if(temp < 20 && light < 500 && !motion) mode = 0;
  else if(temp > 30 && motion) mode = 2;
  else if(light < 500 && motion) mode = 3;
  if(obstacle) mode = 3;

  if(mode != previousMode){
    passiveBeep(mode);
    previousMode = mode;
  }

  bool alarmActive = (mode == 3 || obstacle);
  activeAlarm(alarmActive);
  digitalWrite(RELAY1, alarmActive ? LOW : HIGH);

  // ===== OLED YAZDIR =====
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Temp: "); display.print(temp); display.println(" C");
  display.print("Hum : "); display.print(hum); display.println(" %");
  display.print("Light: "); display.println(light);
  display.print("Motion: "); display.println(motion ? "YES" : "NO");
  display.print("Obs: "); display.println(obstacle ? "YES" : "NO");
  display.print("MODE: "); display.println(modeName(mode));
  display.display();
  

  delay(300);
}

