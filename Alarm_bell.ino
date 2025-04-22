#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <Keypad.h>

#define buzzerPin A0
#define maxBells 10

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'} // D = Backspace, # = Enter, B = Stop buzzer
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

struct BellTime {
  byte hour;
  byte minute;
};
BellTime bellSchedule[maxBells];
byte numBells = 0;
bool bellRinging = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT);

  if (!rtc.begin()) {
    lcd.print("RTC ERROR");
    while (1);
  }

  // Set RTC only once by uncommenting below, then re-upload with it commented
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.setCursor(0, 0);
  lcd.print("CLG BELL SYSTEM");
  delay(2000);
  lcd.clear();
  loadBellSchedule();
}

void loop() {
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print(now.year());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.day());

  lcd.setCursor(0, 1);
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());

  if (!bellRinging) {
    for (byte i = 0; i < numBells; i++) {
      if (bellSchedule[i].hour == now.hour() && bellSchedule[i].minute == now.minute() && now.second() == 0) {
        ringBell(i + 1); // Pass bell number (1st bell, 2nd, etc.)
      }
    }
  }

  char key = keypad.getKey();
  if (key == '*') {
    menu();
  }

  delay(1000);
}

void ringBell(byte bellNumber) {
  bellRinging = true;
  for (byte i = 0; i < bellNumber; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);

    // Allow STOP by pressing 'B'
    unsigned long waitStart = millis();
    while (millis() - waitStart < 1000) {
      char key = keypad.getKey();
      if (key == 'B') {
        digitalWrite(buzzerPin, LOW);
        bellRinging = false;
        return;
      }
    }
  }
  bellRinging = false;
}

void menu() {
  lcd.clear();
  lcd.print("1:Set Time");
  lcd.setCursor(0, 1);
  lcd.print("2:Set Bells");
  delay(1000);
  char key = keypad.waitForKey();
  if (key == '1') {
    setTime();
  } else if (key == '2') {
    setBellSchedule();
  }
}

void setTime() {
  lcd.clear();
  lcd.print("Set Year:");
  int year = getNumber();
  lcd.clear();
  lcd.print("Set Month:");
  int month = getNumber();
  lcd.clear();
  lcd.print("Set Day:");
  int day = getNumber();
  lcd.clear();
  lcd.print("Set Hour:");
  int hour = getNumber();
  lcd.clear();
  lcd.print("Set Minute:");
  int minute = getNumber();
  lcd.clear();
  rtc.adjust(DateTime(year, month, day, hour, minute, 0));
}

void setBellSchedule() {
  lcd.clear();
  lcd.print("No of Bells:");
  numBells = getNumber();
  for (byte i = 0; i < numBells; i++) {
    lcd.clear();
    lcd.print("Bell "); lcd.print(i + 1);
    lcd.setCursor(0, 1);///cursorrrr 
    lcd.print("Hour:");
    bellSchedule[i].hour = getNumber();
    lcd.clear();
    lcd.print("Minute:");
    bellSchedule[i].minute = getNumber();
    lcd.clear();
  }
  saveBellSchedule();
}

int getNumber() {
  String input = "";
  lcd.setCursor(6, 1);
  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key == '#') {
        break;
      } else if (key == 'D') { // Backspace
        if (input.length() > 0) {
          input.remove(input.length() - 1);
          lcd.setCursor(6, 1);
          lcd.print("    "); // Clear the whole 4-digit space
          lcd.setCursor(6, 1);
          lcd.print(input);
        }
      } else if (isdigit(key)) {
        if (input.length() < 4) {
          input += key;
          lcd.print(key);
        }
      }
    }
  }
  return input.toInt();
}

void saveBellSchedule() {
  EEPROM.write(0, numBells);
  for (byte i = 0; i < numBells; i++) {
    EEPROM.write(i * 2 + 1, bellSchedule[i].hour);
    EEPROM.write(i * 2 + 2, bellSchedule[i].minute);
  }
}

void loadBellSchedule() {
  numBells = EEPROM.read(0);
  for (byte i = 0; i < numBells; i++) {
    bellSchedule[i].hour = EEPROM.read(i * 2 + 1);
    bellSchedule[i].minute = EEPROM.read(i * 2 + 2);
  }
}
