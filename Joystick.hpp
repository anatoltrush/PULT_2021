#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include <LiquidCrystal.h>

#include "Defines.hpp"

#define DEBUG_JOY

class Joystick {
	bool is_defined = false;
	bool is_left = false;

	uint8_t differ_x = 0;
	uint8_t differ_y = 0;
	uint8_t x_pin = 0;
	uint8_t y_pin = 0;
	uint8_t sw_pin = 0;

	uint32_t _period = 0; // period
	uint32_t _prev_mills_calc = 0; // last read
	uint32_t _prev_mills_show = 0; // last show
public:
	Joystick(uint8_t x_p, uint8_t y_p, uint8_t sw_p, uint32_t per, bool is_lft);

	void update(uint8_t& dataX, uint8_t& dataY, uint8_t& dataSW);
	void on_lcd(LiquidCrystal& lcd, uint8_t x, uint8_t y, uint8_t sw);
};
#endif // JOYSTICKPP
