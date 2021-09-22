#include "Extra.hpp"
#include "WrapRadio.hpp"
#include "Joystick.hpp"

Extra extra(PIN_FLASH, PIN_VOLT);
WrapRadio wrapradio;
Joystick joy_left(PIN_JOY_LEFT_X, PIN_JOY_LEFT_Y, PIN_JOY_LEFT_SW, TIME_READ_JOY_MS, true);
Joystick joy_right(PIN_JOY_RIGHT_X, PIN_JOY_RIGHT_Y, PIN_JOY_RIGHT_SW, TIME_READ_JOY_MS, false);

uint8_t msg_data[SIZE_OF_DATA] = { 0 };

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  Serial.println("PULT_2021");
}

void loop() {
  extra.flash(TIME_FLASH_MS); // heart beat

  joy_left.update(msg_data[0], msg_data[1], msg_data[2]);
  joy_right.update(msg_data[3], msg_data[4], msg_data[5]);
}

// calib joy -> constr
// joy change timestyle
