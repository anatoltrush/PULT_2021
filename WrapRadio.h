#ifndef WRAPRADIO_H
#define WRAPRADIO_H

#include <RF24.h>

#include "Defines.h"

//#define DEBUG_RADIO

class WrapRadio
{
  public:
    RF24* radio = NULL;

    uint8_t pipeNum = 0;
    // ACK bytes: 0 - quad volt, 1 - is max reached, 2 - num of motor
    uint8_t ack_msg[SIZE_OF_ACK] = {0};
    // left[1]throttle, left[0]yaw, right[4]pitch, right[3]roll
    uint8_t msg_data[SIZE_OF_DATA] = {0};

    bool isConnQualReady = false;
    uint8_t connQualPerc = 0;

    WrapRadio();
    ~WrapRadio();

    void init();
    bool sendTimer(uint32_t ms);

  private:
    uint8_t countGoodTry = 0;
    uint8_t countAllTry = 0;
    const uint16_t allPackets = TIME_CONN_UPD_MS / TIME_SEND_DATA_MS;

    uint32_t prevSendMs = 0;

    void updCount();
};
#endif // WRAPRADIO_H
