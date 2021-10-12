#include "WrapLCD.h"

WrapLCD::WrapLCD(LiquidCrystal& lcd) {
  uint8_t kvadrokopter[8] = { // 0
    0b00000,
    0b11011,
    0b11011,
    0b00100,
    0b00100,
    0b11011,
    0b11011,
    0b00000
  };
  uint8_t battary[8] = { // 1
    0b00010,
    0b00100,
    0b01000,
    0b11111,
    0b00010,
    0b00100,
    0b01000,
    0b00000
  };
  uint8_t pult[8] = { // 2
    0b00100,
    0b00100,
    0b00100,
    0b11111,
    0b10001,
    0b11011,
    0b10001,
    0b11111
  };
  uint8_t connection[8] = { // 3
    0b11111,
    0b10000,
    0b11110,
    0b10000,
    0b11100,
    0b10000,
    0b11000,
    0b10000
  };
  uint8_t lev2[8] = { // 4
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111
  };
  uint8_t lev3[8] = { // 5
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
  };
  uint8_t lev4[8] = { // 6
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
  };
  uint8_t empty[8] = {  // 7 (reserved)
    0b01010,
    0b10101,
    0b01010,
    0b10101,
    0b01010,
    0b10101,
    0b01010,
    0b10101
  };

  lcd.createChar(0, kvadrokopter);
  lcd.createChar(1, battary);
  lcd.createChar(2, pult);
  lcd.createChar(3, connection);
  lcd.createChar(4, lev2);
  lcd.createChar(5, lev3);
  lcd.createChar(6, lev4);
  lcd.createChar(7, empty);
}

void WrapLCD::lcdInitialization(LiquidCrystal& lcd) {
  lcd.setCursor(1, 0);
  lcd.print("REMOTE CONTROL");
  lcd.setCursor(1, 1);
  lcd.print("INITIALIZATION");
  delay(500);
  for (byte str = 0; str < 2; str++) {
    for (byte stl = 0; stl < 16; stl++) {
      lcd.setCursor(stl, str);
      lcd.print("X");
      delay(25);
    }
  }
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.write(byte(0));

  lcd.setCursor(1, 0);
  lcd.write(byte(1));

  lcd.setCursor(0, 1);
  lcd.write(byte(2));

  lcd.setCursor(1, 1);
  lcd.write(byte(1));

  lcd.setCursor(11, 0);
  lcd.write(byte(3));

  //---------------------
  lcd.setCursor(9, 1);
  lcd.write(">");
  lcd.setCursor(10, 1);
  lcd.write("_");
  lcd.setCursor(11, 1);
  lcd.write("_");
  lcd.setCursor(12, 1);
  lcd.write("_");
  lcd.setCursor(13, 1);
  lcd.write("_");
  lcd.setCursor(14, 1);
  lcd.write("_");
  lcd.setCursor(15, 1);
  lcd.write("_");
}

void WrapLCD::powerACK(LiquidCrystal& lcd, uint8_t* ack_data, uint32_t ms) {
  if (millis() - prevMillisWarnMs >= ms) {
#ifdef DEBUG_LCD
    Serial.print(millis() - prevMillisWarnMs);
    Serial.print("_");
    Serial.print(__func__);
    Serial.print("_");
    Serial.println(ack_data[BT_ACK_WARN]);
#endif
    prevMillisWarnMs = millis();
    //_________________________
    // 1 is max reached & 2 number of motor
    lcd.setCursor(14, 0);
    if (ack_data[BT_ACK_WARN] != 0) {
      (warnState) ? lcd.write("!") : lcd.write(" ");
      warnState = ! warnState;
    }
    else {
      lcd.write("-");
    }
    lcd.setCursor(15, 0);
    lcd.print(ack_data[BT_ACK_NUME]);
    // 3 main power
    lcd.setCursor(10, 0);
    if (ack_data[BT_ACK_POWR] >= 0 && ack_data[BT_ACK_POWR] < 10){
      lcd.print(ack_data[BT_ACK_POWR]);
      Serial.println(ack_data[BT_ACK_POWR]);
    }
    else
    lcd.print("-");
  }
}

void WrapLCD::connQuality(LiquidCrystal& lcd, uint8_t quality, uint32_t ms) {
  if (millis() - prevMillisQualMs >= ms) {
#ifdef DEBUG_LCD
    Serial.print(millis() - prevMillisQualMs);
    Serial.print("_");
    Serial.print(__func__);
    Serial.print("_");
    Serial.println(quality);
#endif
    prevMillisQualMs = millis();
    //_________________________
    if (quality < 10) {
      lcd.setCursor(12, 0);
      lcd.print(" ");
      lcd.setCursor(13, 0);
    }
    else {
      lcd.setCursor(12, 0);
    }
    lcd.print(quality);
  }
}
