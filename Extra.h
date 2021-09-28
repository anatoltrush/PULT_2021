#ifndef EXTRA_H
#define EXTRA_H

#include <LiquidCrystal.h>

#include "Defines.h"

//#define DEBUG_EXTRA

class Extra
{
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

  public:
    Extra(uint8_t led_pin, uint8_t volt_pin);

    float voltResRc = 0.0f;

    void flash(uint32_t ms);
    void getVoltRc(uint32_t ms);

    void showVoltQuad(LiquidCrystal& lcd, uint32_t ms, uint8_t quadVolt);
    void showVoltRemContrl(LiquidCrystal& lcd, uint32_t ms);
};

#endif // EXTRA_H
