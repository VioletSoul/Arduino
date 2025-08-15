#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// display 16x2 at 0x27 addr
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pirPin = 2; // 2nd pin for PIR-sensor

void setup() {
  pinMode(pirPin, INPUT);

  lcd.init();      // disp init
  lcd.backlight(); // backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ожидание...");
}

void loop() {
  int motion = digitalRead(pirPin);

  if (motion == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Обнаружено");
    lcd.setCursor(0, 1);
    lcd.print("движение!");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Нет движения");
    lcd.setCursor(0, 1);
    lcd.print("Ожидание...");
  }

  delay(500); // every 0.5 sec
}
