#include "Extra.h"

Extra::Extra(uint8_t led_pin, uint8_t volt_pin):
  flashPin(led_pin), voltPin(volt_pin) {
  pinMode(flashPin, OUTPUT);
  pinMode(voltPin, INPUT);
}

void Extra::flash(uint32_t ms) {
  if (millis() - prevFlashMs >= ms) {
#ifdef DEBUG_EXTRA
    Serial.print(millis() - prevFlashMs);
    Serial.print("_");
    Serial.println(__func__);
#endif
    prevFlashMs = millis();
    //_________________________
    (ledState == LOW) ? ledState = HIGH : ledState = LOW;

    digitalWrite(flashPin, ledState);
  }
}

void Extra::getVoltRc(uint32_t ms) {
  if (millis() - prevVoltGetMs >= ms) {
#ifdef DEBUG_EXTRA
    Serial.print(millis() - prevVoltGetMs);
    Serial.print("_");
    Serial.println(__func__);
#endif
    prevVoltGetMs = millis();
    //_________________________
    uint16_t readSignal = analogRead(voltPin);
    voltResRc = (float)readSignal / VOLT_DIV;
    // in percents
    float diffCurr = voltResRc - VOLT_MIN_RC;
    voltPercentRc = (diffCurr / diffMinMaxRc) * 100;
    if (voltPercentRc >= 100) voltPercentRc = 99;
  }
}

void Extra::showVoltQuad(LiquidCrystal& lcd, uint32_t ms, uint8_t quadVolt) {
  if (millis() - prevVoltLcdQdMs >= ms) {
#ifdef DEBUG_EXTRA
    Serial.print(millis() - prevVoltLcdQdMs);
    Serial.print("_");
    Serial.println(__func__);
#endif
    prevVoltLcdQdMs = millis();
    //_________________________
    // ---perc---
    lcd.setCursor(2, 0);
    float diffCurr = (quadVolt / 10.0f) - VOLT_MIN_QD;
    voltPercentQd = (diffCurr / diffMinMaxQd) * 100;
    if (voltPercentQd >= 100) voltPercentQd = 99;
    // ---
    if (voltPercentQd < 0) lcd.print("LOW");
    if (voltPercentQd >= 0 && voltPercentQd < 10) {
      lcd.print(" ");
      lcd.print(voltPercentQd);
      lcd.print("%");
    }
    if (voltPercentQd >= 10) {
      lcd.print(voltPercentQd);
      lcd.print("%");
    }
    // ---abs---
    lcd.setCursor(5, 0);
    lcd.print("     "); // clear prev print
    lcd.setCursor(5, 0);
    dtostrf(quadVolt / 10.0f, 4, 1, CharQuad);
    if (quadVolt >= 10.0f) {
      for (int i = 0; i < 4; i++)
        lcd.print(CharQuad[i]);
    }
    else {
      for (int i = 1; i < 4; i++)
        lcd.print(CharQuad[i]);
    }
    lcd.print("V");
  }
}

void Extra::showVoltRemContrl(LiquidCrystal& lcd, uint32_t ms) {
  if (millis() - prevVoltLcdRcMs >= ms) {
#ifdef DEBUG_EXTRA
    Serial.print(millis() - prevVoltLcdRcMs);
    Serial.print("_");
    Serial.println(__func__);
#endif
    prevVoltLcdRcMs = millis();
    //_________________________
    // ---perc---
    lcd.setCursor(2, 1);
    if (voltPercentRc < 0) lcd.print("LOW");
    if (voltPercentRc >= 0 && voltPercentRc < 10) {
      lcd.print(" ");
      lcd.print(voltPercentRc);
      lcd.print("%");
    }
    if (voltPercentRc >= 10) {
      lcd.print(voltPercentRc);
      lcd.print("%");
    }
    // ---abs---
    lcd.setCursor(5, 1);
    dtostrf(voltResRc, 4, 1, CharRCntrl);
    if (voltResRc >= 10.0f) {
      for (int i = 0; i < 4; i++)
        lcd.print(CharRCntrl[i]);
    }
    else {
      for (int i = 1; i < 4; i++)
        lcd.print(CharRCntrl[i]);
    }
    lcd.print("V");
  }
}
