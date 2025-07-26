#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastRead = 0;
const unsigned long READ_INTERVAL = 1000;

float humidity = NAN, temperature = NAN;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
  lcd.clear();
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= READ_INTERVAL) {
    lastRead = now;
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Error read DHT11");
      lcd.setCursor(0, 0);
      lcd.print("Sensor error     ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      return;
    }
    humidity = h + 10;
    temperature = t - 2;

    Serial.print("Влажность: ");
    Serial.print(humidity, 1);
    Serial.print(" %\t");

    Serial.print("Темп.: ");
    Serial.print(temperature, 1);
    Serial.println(" *C");
  }

  static float prevHumidity = NAN, prevTemperature = NAN;
  if (humidity != prevHumidity || temperature != prevTemperature) {
    String humStr = String(humidity, 1) + " %";
    String humLab = "Humidity:";
    int humPos = 16 - humStr.length();

    lcd.setCursor(0, 0);
    lcd.print(humLab);
    lcd.setCursor(humPos, 0);
    lcd.print(humStr);

    String tempStr = String(temperature, 1) + " C";
    String tempLab = "Temp:";
    int tempPos = 16 - tempStr.length();

    lcd.setCursor(0, 1);
    lcd.print(tempLab);
    lcd.setCursor(tempPos, 1);
    lcd.print(tempStr);

    prevHumidity = humidity;
    prevTemperature = temperature;
  }
}

//#include <EEPROM.h>
//void setup() {
//  for (int i = 0; i < EEPROM.length(); i++) {
//    EEPROM.write(i, 255); // 'чистое' состояние — 255
//  }
//}
//void loop() {}

//void setup() {}
//void loop() {}

