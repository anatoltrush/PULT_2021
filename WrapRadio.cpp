#include "WrapRadio.h"

WrapRadio::WrapRadio() {
  radio = new RF24(PIN_NRF_CE, PIN_NRF_CS);
}

WrapRadio::~WrapRadio() {
  delete radio;
}

void WrapRadio::init() {
  if (radio != NULL) {
    radio->begin();
    radio->setAutoAck(true);
    radio->enableAckPayload();
    radio->setPayloadSize(SIZE_OF_DATA);

    radio->openWritingPipe(0x7878787878LL);
    radio->setChannel(0x60);

    radio->setPALevel(RF24_PA_MAX); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
    radio->setDataRate(RF24_1MBPS); // RF24_2MBPS, RF24_1MBPS, RF24_250KBPS

    radio->powerUp();
    radio->stopListening();
  }
  else {
    Serial.println("Null pointer in WrapRadio");
  }
}

void WrapRadio::updCount() {
  countAllTry++;
  if (countAllTry >= allPackets - 1) {
    connQualPerc = (countGoodTry * 100) / countAllTry;
    if (connQualPerc >= 100)connQualPerc = 99;
    countGoodTry = 0;
    countAllTry = 0;
  }
}

void WrapRadio::sendTimer(uint32_t ms) {
  if (millis() - prevSendMs >= ms) {
#ifdef DEBUG_RAD
    Serial.print(millis() - prevSendMs); Serial.print("_");
    Serial.println(__func__);
#endif
    prevSendMs = millis();
    //_________________________
    updCount();
    //_________________________
    for (size_t i = 0; i < SIZE_OF_ACK; i++) // DROP ALL ACK
      ack_msg[i] = 0;
    ack_msg[BT_ACK_POWR] = 10;
    //_________________________
    if (radio->write(msg_data, SIZE_OF_DATA)) { // ---> OK CONNECTION <---
      countGoodTry++;
      if (radio->available()) { // READ ACK
        while (radio->available()) { // OK ACK
          radio->read(ack_msg, SIZE_OF_ACK);
#ifdef DEBUG_RAD
          uint8_t* uint8_t_ack = static_cast<uint8_t*>(ack_msg);
          Serial.print("Answer 0: "); Serial.println((int)uint8_t_ack[BT_ACK_VOLT]); // enter number of byte
          Serial.print("Answer 1: "); Serial.println((int)uint8_t_ack[BT_ACK_WARN]);
#endif //DEBUG_RAD
        }
      }
      else { // NO ACK
#ifdef DEBUG_RAD
        Serial.println("Empty ack");
#endif // DEBUG_RAD
      }
    }
    else { // ---> NO CONNECTION <---
#ifdef DEBUG_RAD
      Serial.println("Connection error");
#endif // DEBUG_RAD
    }
  }
}

Extra::Extra() {
  pinMode(pinFlash, OUTPUT);
  pinMode(pinVolt, INPUT);
}

void Extra::flash(uint32_t ms) {
  if (millis() - prevFlashMs >= ms) {
#ifdef DEBUG_EXTRA
    Serial.print(millis() - prevFlashMs); Serial.print("_");
    Serial.println(__func__);
#endif
    prevFlashMs = millis();
    //_________________________
    (stateLed == LOW) ? stateLed = HIGH : stateLed = LOW;
    digitalWrite(pinFlash, stateLed);
  }
}

void Extra::getVoltRc(uint32_t ms) {
  if (millis() - prevVoltGetMs >= ms) {
#ifdef DEBUG_EXTRA
    Serial.print(millis() - prevVoltGetMs); Serial.print("_");
    Serial.println(__func__);
#endif
    prevVoltGetMs = millis();
    //_________________________
    uint16_t readSignal = analogRead(pinVolt);
    voltResRc = ((float)readSignal - VOLT_COEFF_B) / VOLT_COEFF_K;
    // in percents
    float diffCurr = voltResRc - VOLT_MIN_RC;
    voltPercentRc = (diffCurr / diffMinMaxRc) * 100;
    if (voltPercentRc >= 100) voltPercentRc = 99;
    //Serial.print("rc volt: "); Serial.println(readSignal);
  }
}

void Extra::showVoltQuad(LiquidCrystal& lcd, uint32_t ms, uint8_t quadVolt) {
  if (millis() - prevVoltLcdQdMs >= ms) {
#ifdef DEBUG_EXTRA
    Serial.print(millis() - prevVoltLcdQdMs); Serial.print("_");
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
    if (quadVolt / 10.0f >= 10.0f) {
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
    Serial.print(millis() - prevVoltLcdRcMs); Serial.print("_");
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
    if (voltResRc < 0.0f) {
      lcd.print("0.0");
    }
    else if (voltResRc >= 10.0f) {
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
