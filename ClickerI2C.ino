//Версия кликера 1.0
//Пины для подключения
/*
  GND - GND
  VCC - 5V
  SDA - A4
  SCL - A5
  Button - Pin 2
  Button Cheat - Pin 3
*/
#define WIFI_SSID "Keenetic Extra"
#define WIFI_PASS "EF-Legion25"
#define BOT_TOKEN "7979180547:AAHGCICj1mw4csc5G6ie7WbCcNmQ0Z3_uJU"

#include <Wire.h> 
#include <LiquidCrystal_I2C_ESP32.h>
#include <FastBot2.h>
const int Button = 13;
const int ButtonC = 19;
const int Buzz = 23;
int tgclick = 0;
int tgcheat = 0;
int clicks = 0;
int antibug = 0;
int cheat = 0;
int confirm = 0;
int delayt = 150;
String text = "Клик! ; Читануть \n Удалить ; Баланс";

FastBot2 bot;
LiquidCrystal_I2C lcd(0x27,20,4);  // Айди дисплея 0x27 проверить можно в программе https://github.com/PetyaBorisov

void setup() {
  Serial.begin(9600);
  connectWiFi();
  pinMode(Button, INPUT_PULLUP);
  pinMode(ButtonC, INPUT_PULLUP);
  pinMode(Buzz, OUTPUT);
  lcd.init();                      // ДИСПЛЕЙ ЗАПУСКАЙСЯ
  lcd.init();                      // Тебе лень? ДАВАЙ БЫСТРО ЗАПУСКАЙСЯ
  lcd.backlight();                 // Освещение обязательно
  bot.setToken(BOT_TOKEN);
  bot.onUpdate(update);
  Start();
  // Print a message to the LCD.
  lcd.clear();
  lcd.setCursor(0,0);              // Ну и куда текст совать будем???
  lcd.print("Click to Button");    // Псс. Подскажи ему как
  lcd.setCursor(0,1);              // Скоко кликов?
  lcd.print("Clicks:");            // Кликов сколько говорю
  lcd.setCursor(8,1);              // Я СКАЗАЛ СКОЛЬКО КЛИКОВ
  lcd.print(clicks);               // Так бы и сказал
}

void loop() {
  bot.tick();
  if (digitalRead(Button) == 0 || tgclick == 1) {
    if (antibug == 1 && tgclick == 0) {
      buguse();
    }
    else if (antibug > 1) {
      antibug = 0;
    }
    antibug++;
    delay(delayt);                    // Ладно спи 150 миллисекунд
    lcd.clear();                   // ПОДЬЁМ чистим
    clicks++;
    lcd.setCursor(0,0);
    lcd.print("Clicks: ");
    lcd.setCursor(8,0);
    lcd.print(clicks);
    if (clicks == 5000) {
      lcd.setCursor(0,1);
      lcd.print("Cheats available!");
    }
  }
  else if (digitalRead(ButtonC) == 0 && cheat == 0 && clicks >= 5000 || cheat == 0 && clicks >= 5000 && tgcheat == 1) {
    digitalWrite(Buzz, HIGH);
    delay(200);
    digitalWrite(Buzz, LOW);
    lcd.clear();
    lcd.print("Are you sure?");
    delay(500);
    if (digitalRead(ButtonC) == 0) {
      cheat++;
      delayt = 0;
      lcd.clear();
      lcd.print("Cheats enabled");
      CheatE();
    }
  }
  else if (digitalRead(ButtonC) == 0 && cheat == 1 || cheat == 1 && tgcheat == 1) {
    lcd.setCursor(0,1);
    lcd.print("Cheats disabled");
    cheat--;
    delayt = 150;
    CheatD();
  }
  else if (digitalRead(ButtonC) == 0 && clicks < 5000 || clicks < 5000 && tgcheat == 1) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("5000 Clicks");
    lcd.setCursor(0,1);
    lcd.print("for open cheats");
  }
}

void buguse() {
  if (digitalRead(Button) == LOW && delayt == 150) {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Do not use bug!");
  }
  else if (digitalRead(Button) == HIGH) {
    antibug -= 1;
  }
}

void update(fb::Update& u) {
  
}

void Start() {
  while (digitalRead(Button) == 1) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hello!");
    lcd.setCursor(0,1);
    lcd.print("By PetyaBorisov");
    delay(2000);
    lcd.clear();
    lcd.print("Game: Clicker");
    lcd.setCursor(0,1);
    lcd.print("v2.0 Beta");
    delay(1000);
  }
}

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}

void CheatE() {
  digitalWrite(Buzz, HIGH);
  delay(500);
  digitalWrite(Buzz, LOW);
  delay(300);
  digitalWrite(Buzz, HIGH);
  delay(500);
  digitalWrite(Buzz, LOW);
}
void CheatD() {
  digitalWrite(Buzz, HIGH);
  delay(500);
  digitalWrite(Buzz, LOW);
}
