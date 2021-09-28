#ifndef EXTRA_H
#define EXTRA_H

#include "Defines.h"

//#define DEBUG_EXTRA

class Extra
{
  private:
    uint8_t flashPin = PIN_FLASH;
    uint8_t voltPin  = PIN_VOLT;

    uint8_t voltPercent = 0;

    uint32_t prevFlashMs = 0;
    uint32_t prevVoltMs = 0;

    bool ledState = false;

    float diffMinMax = MAX_VOLT - MIN_VOLT;

  public:
    Extra(uint8_t led_pin, uint8_t volt_pin);

    float voltOutput = 0.0f;

    void flash(uint32_t ms);
    void getVolt(uint32_t ms);
};

#endif // EXTRA_H