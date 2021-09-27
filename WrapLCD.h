#ifndef WRAPLCD_H
#define WRAPLCD_H

#include <LiquidCrystal.h>

#include "Defines.h"

#define DEBUG_LCD

class WrapLCD
{
  public:
    WrapLCD(LiquidCrystal& lcd);

    void lcdInitialization(LiquidCrystal& lcd);

    void analyzeACK(LiquidCrystal& lcd, uint8_t* ack_data, uint32_t ms);

    void connQuality(LiquidCrystal& lcd, bool& isReady, uint8_t quality, uint32_t ms);

  private:
    uint32_t prevMillisWarnMs = 0;
    uint32_t prevMillisQualMs = 0;
    
    bool warnState = false;
};

#endif // WRAPLCD_H
