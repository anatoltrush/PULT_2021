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

bool WrapRadio::sendTimer(uint32_t ms) {
  if (millis() - prevSendMs >= ms) {
#ifdef DEBUG_RADIO
    Serial.print(millis() - prevSendMs);
    Serial.print("_");
    Serial.println(__func__);
#endif
    prevSendMs = millis();
    //_________________________
    updCount();
    //_________________________
    for (size_t i = 0; i < SIZE_OF_ACK; i++) // drop all ack
      ack_msg[i] = 0;
    //_________________________
    if (radio->write(msg_data, SIZE_OF_DATA)) { // ---> OK CONNECTION <---
      countGoodTry++;
      if (radio->available()) { // READ ACK
        while (radio->available()) { // OK ACK
          radio->read(ack_msg, SIZE_OF_ACK);
          // do smthng
#ifdef DEBUG_RADIO
          uint8_t* uint8_t_ack = static_cast<uint8_t*>(ack_msg);
          Serial.print("Answer 0: "); Serial.println((int)uint8_t_ack[0]); // enter number of byte
          Serial.print("Answer 1: "); Serial.println((int)uint8_t_ack[1]);
          Serial.print("Answer 2: "); Serial.println((int)uint8_t_ack[2]);
#endif //DEBUG_RADIO
        }
      }
      else { // NO ACK
#ifdef DEBUG_RADIO
        Serial.println("Empty ack");
#endif //DEBUG_RADIO
      }
    }
    else { // ---> NO CONNECTION <---
#ifdef DEBUG_RADIO
      Serial.println("Connection error");
#endif // DEBUG_RADIO
    }
  }
}
