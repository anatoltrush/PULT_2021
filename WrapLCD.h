#ifndef WRAPLCD_H
#define WRAPLCD_H

#include "Defines.h"

//#define DEBUG_LCD

class WrapLCD
{
  public:
    WrapLCD(LiquidCrystal& lcd);

    bool warnState = false;

    void lcdInitialization(LiquidCrystal& lcd);

    void powerACK(LiquidCrystal& lcd, uint8_t* ack_data, uint32_t ms);

    void connQuality(LiquidCrystal& lcd, uint8_t quality, uint32_t ms);

  private:
    uint8_t pinVibro = PIN_VIBRO;

    uint32_t prevMillisWarnMs = 0;
    uint32_t prevMillisQualMs = 0;
};

#endif // WRAPLCD_H
