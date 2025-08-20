#include <Keypad.h>
#include <LiquidCrystal.h>

// Настройки для дисплея
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Параметры Keypad
const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; // к выводам Arduino Uno
byte colPins[COLS] = {A4, A5, 2, 3};   // к выводам Arduino Uno

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = "";

void setup() {
  lcd.begin(20, 4);
  lcd.clear();
  lcd.print("Введите цифры:");
  lcd.setCursor(0, 1);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key >= '0' && key <= '9') {
      if (input.length() < 20 * 3) { // до 3 строк — 60 символов
        input += key;
        updateLCD();
      }
    } else if (key == '*') { // Стереть последний символ
      if (input.length() > 0) {
        input.remove(input.length()-1);
        updateLCD();
      }
    } else if (key == '#') { // Очистить все
      input = "";
      updateLCD();
    }
  }
}

void updateLCD() {
  lcd.clear();
  lcd.print("Введите цифры:");
  for (int i = 0; i < input.length(); i++) {
    int row = i / 20 + 1;
    int col = i % 20;
    if (row < 4) {
      lcd.setCursor(col, row);
      lcd.print(input[i]);
    }
  }
}
