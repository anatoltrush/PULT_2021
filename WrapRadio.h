#ifndef WRAPRADIO_H
#define WRAPRADIO_H

#include <RF24.h>

#include "Defines.h"

//#define DEBUG_RAD

class WrapRadio
{
  public:
    WrapRadio();
    ~WrapRadio();

    RF24* radio = NULL;

    uint8_t pipeNum = 0;

    // ACK bytes: 0 - quad volt, 1 - is max reached, 2 - num of motor, 3 - main power
    uint8_t ack_msg[SIZE_OF_ACK] = {0};

    // left[1]throttle, left[0]yaw, right[4]pitch, right[3]roll
    uint8_t msg_data[SIZE_OF_DATA] = {0};

    uint8_t connQualPerc = 0;

    void init();
    void sendTimer(uint32_t ms);

  private:
    uint8_t countGoodTry = 0;
    uint8_t countAllTry = 0;
    const uint16_t allPackets = TIME_CONN_UPD_MS / TIME_SEND_DATA_MS;

    uint32_t prevSendMs = 0;

    void updCount();
};

//#define DEBUG_EXTRA

class Extra
{
  public:
    Extra();

    float voltResRc = 0.0f;

    void flash(uint32_t ms);
    void getVoltRc(uint32_t ms);

    void showVoltQuad(LiquidCrystal& lcd, uint32_t ms, uint8_t quadVolt);
    void showVoltRemContrl(LiquidCrystal& lcd, uint32_t ms);

  private:
    char CharQuad[5];
    char CharRCntrl[5];

    uint8_t flashPin = PIN_FLASH;
    uint8_t voltPin  = PIN_VOLT;

    int16_t voltPercentRc = 0;
    int16_t voltPercentQd = 0;

    uint32_t prevFlashMs = 0;
    uint32_t prevVoltGetMs = 0;
    uint32_t prevVoltLcdQdMs = 0;
    uint32_t prevVoltLcdRcMs = 0;

    bool ledState = false;

    float diffMinMaxRc = VOLT_MAX_RC - VOLT_MIN_RC;
    float diffMinMaxQd = VOLT_MAX_QD - VOLT_MIN_QD;
};
#endif // WRAPRADIO_H
