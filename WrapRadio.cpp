#include "WrapRadio.hpp"

WrapRadio::WrapRadio() {
  radio = new RF24(PIN_NRF_CE, PIN_NRF_CS);
}

WrapRadio::~WrapRadio() {
  delete radio;
}

void WrapRadio::init() {
  if (radio != NULL) {
    uint8_t address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

    radio->begin();
    radio->setAutoAck(true);
    radio->setRetries(5, 1);
    radio->enableAckPayload();
    radio->setPayloadSize(SIZE_OF_DATA);

    radio->openWritingPipe(address[0]);
    radio->setChannel(0x60);

    radio->setPALevel(RF24_PA_MAX); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
    radio->setDataRate(RF24_1MBPS); // RF24_2MBPS, RF24_1MBPS, RF24_250KBPS

    radio->powerUp();
    radio->stopListening();
  }
}

bool WrapRadio::sendTimer(const void* data, void* ack, uint32_t ms) {
  if (millis() - prev_ms_send >= ms) {
#ifdef DEBUG_RADIO
    Serial.print(millis() - prev_ms_send);
    Serial.print("_");
    Serial.println(__func__);
#endif
    prev_ms_send = millis();
    //_________________________
    if (radio->write(data, SIZE_OF_DATA)) {
      if (radio->available()) { // READ ACK
        while (radio->available()) {
          radio->read(ack, SIZE_OF_ACK);
          // do smthng
#ifdef DEBUG_RADIO
          uint8_t* uint8_t_ack = static_cast<uint8_t*>(ack);
          Serial.print("Answer: "); Serial.println((int)uint8_t_ack[0]); // enter number of byte
#endif //DEBUG_RADIO
        }
      }
      else {
#ifdef DEBUG_RADIO
        Serial.println("Empty ack");
#endif //DEBUG_RADIO
      }
    }
    else {
      //volt.is_conn = false;
#ifdef DEBUG_RADIO
      Serial.println("Connection error");
#endif // DEBUG_RADIO
    }
  }
}
