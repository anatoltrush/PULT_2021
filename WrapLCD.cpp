#include "WrapLCD.h"

WrapLCD::WrapLCD(LiquidCrystal& lcd) {
  uint8_t quad[8] = { // 0
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
  uint8_t remContr[8] = { // 2
    0b00100,
    0b00100,
    0b00100,
    0b11111,
    0b10001,
    0b11011,
    0b10001,
    0b11111
  };
  uint8_t aerial[8] = { // 3
    0b10101,
    0b10101,
    0b01110,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00000
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

  lcd.createChar(0, quad);
  lcd.createChar(1, battary);
  lcd.createChar(2, remContr);
  lcd.createChar(3, aerial);
  lcd.createChar(4, lev2);
  lcd.createChar(5, lev3);
  lcd.createChar(6, lev4); // 7 is empty (reserved)
}

void WrapLCD::lcdInitialization(LiquidCrystal& lcd) {
  lcd.setCursor(1, 0);
  lcd.print("REMOTE CONTROL");
  lcd.setCursor(1, 1);
  lcd.print("INITIALIZATION");
  delay(400);
  for (byte str = 0; str < 2; str++) {
    for (byte stl = 0; stl < 16; stl++) {
      lcd.setCursor(stl, str);
      lcd.print("X");
      delay(20);
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
}

void WrapLCD::powerACK(LiquidCrystal& lcd, uint8_t* ack_data, uint32_t ms) {
  if (millis() - prevMillisWarnMs >= ms) {
#ifdef DEBUG_LCD
    Serial.print(millis() - prevMillisWarnMs); Serial.print("_");
    Serial.print(__func__); Serial.print("_");
    Serial.println(ack_data[BT_ACK_WARN]);
#endif
    prevMillisWarnMs = millis();
    //_________________________
    // 1 isMaxReached & 2 number of motor
    lcd.setCursor(14, 0);
    if (ack_data[BT_ACK_WARN] != 0) {
      (warnState) ? lcd.write("!") : lcd.write(" ");
      warnState = ! warnState;
    }
    else {
      lcd.write("-");
      warnState = false;
    }
    lcd.setCursor(15, 0);
    lcd.print(ack_data[BT_ACK_NUME]);
    // 3 main power
    lcd.setCursor(10, 0);
    if (ack_data[BT_ACK_POWR] >= 0 && ack_data[BT_ACK_POWR] < 10)
      lcd.print(ack_data[BT_ACK_POWR]);
    else
      lcd.print("-");
    // --- raw voltage --- BT_RAW_VLT1 & BT_RAW_VLT2
    uint8_t rawVoltArr[sizeof (uint16_t)] = {0};
    rawVoltArr[0] = ack_data[BT_RAW_VLT1];
    rawVoltArr[1] = ack_data[BT_RAW_VLT2];
    uint16_t rawVolt = 0;
    memcpy(&rawVolt, rawVoltArr, sizeof (uint16_t));
    //Serial.print("raw quad volt: "); Serial.println(rawVolt);
  }
}

void WrapLCD::connQuality(LiquidCrystal& lcd, uint8_t quality, uint32_t ms) {
  if (millis() - prevMillisQualMs >= ms) {
#ifdef DEBUG_LCD
    Serial.print(millis() - prevMillisQualMs); Serial.print("_");
    Serial.print(__func__); Serial.print("_");
    Serial.println(quality);
#endif
    prevMillisQualMs = millis();
    //_________________________
    lcd.setCursor(12, 0);
    if (quality < 10) {
      lcd.print(" ");
      lcd.setCursor(13, 0);
    }
    lcd.print(quality);
  }
}
