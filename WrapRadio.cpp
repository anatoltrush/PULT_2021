#include "WrapRadio.hpp"

WrapRadio::WrapRadio()
{
  radio = new RF24(PIN_NRF_CE, PIN_NRF_CS);
}

WrapRadio::~WrapRadio()
{
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

void WrapRadio::sendTimer(uint32_t ms) {
  if (millis() - prev_ms_send >= ms) {
    #ifdef DEBUG_RADIO
    Serial.print(millis() - prev_ms_send);
    Serial.print("_");
    Serial.println(__func__);
#endif
    prev_ms_send = millis();
    //_________________________
    // TODO: implement
  }
}
