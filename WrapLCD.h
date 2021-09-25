#ifndef WRAPLCD_H
#define WRAPLCD_H

#include <LiquidCrystal.h>

#include "Defines.h"

class WrapLCD
{
  public:
  WrapLCD(LiquidCrystal& lcd);

  void lcd_initialization(LiquidCrystal& lcd);
  
  private:
  uint32_t prev_millis_warn_max = 0;
};

#endif // WRAPLCD_H
