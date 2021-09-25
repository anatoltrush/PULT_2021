#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <LiquidCrystal.h>

#include "Defines.h"

//#define DEBUG_JOY
#define IS_1_0_DATA

class Joystick {
	bool is_left = false;

	uint8_t differ_x = 0;
	uint8_t differ_y = 0;
	uint8_t x_pin = 0;
	uint8_t y_pin = 0;
	uint8_t sw_pin = 0;

	uint32_t prev_mills_calc = 0; // last read
	uint32_t prev_mills_show = 0; // last show
  
public:
	Joystick(uint8_t x_p, uint8_t y_p, uint8_t sw_p, bool is_lft);

  void init();
	void readData(uint8_t& dataX, uint8_t& dataY, uint8_t& dataSW, uint32_t ms);
	void on_lcd(LiquidCrystal& lcd, uint8_t x, uint8_t y, uint8_t sw, uint32_t ms);
};
#endif // JOYSTICK
