#include <LiquidCrystal.h>

#include "InitLCD.hpp"
#include "Extra.hpp"
#include "WrapRadio.hpp"
#include "Joystick.hpp"

LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

Extra extra(PIN_FLASH, PIN_VOLT);
WrapRadio wrapradio;
Joystick joy_left(PIN_JOY_LEFT_X, PIN_JOY_LEFT_Y, PIN_JOY_LEFT_SW, true);
Joystick joy_right(PIN_JOY_RIGHT_X, PIN_JOY_RIGHT_Y, PIN_JOY_RIGHT_SW, false);

uint8_t msg_data[SIZE_OF_DATA] = {0};
uint8_t ack_data[SIZE_OF_ACK] = {0};

void setup() {
  lcd.begin(16, 2);
  lcd_initialization(lcd);

  Serial.begin(115200);

  wrapradio.init();
  joy_left.init();
  joy_right.init();
}

void loop() {
  extra.flash(TIME_FLASH_MS); // heart beat

  joy_left.readData(msg_data[0], msg_data[1], msg_data[2], TIME_READ_JOY_MS);
  joy_right.readData(msg_data[3], msg_data[4], msg_data[5], TIME_READ_JOY_MS);

  joy_left.on_lcd(lcd, msg_data[0], msg_data[1], msg_data[2], TIME_READ_JOY_MS);
  joy_right.on_lcd(lcd, msg_data[3], msg_data[4], msg_data[5], TIME_READ_JOY_MS);

  wrapradio.sendTimer(&msg_data, &ack_data, TIME_SEND_DATA_MS);
}

// right place of bytes on pult