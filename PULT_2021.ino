#include "WrapLCD.h"
#include "Extra.h"
#include "WrapRadio.h"
#include "Joystick.h"

LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

Extra extra(PIN_FLASH, PIN_VOLT);
WrapRadio wrapRadio;
WrapLCD wrapLCD(lcd);
Joystick joyLeft(PIN_JOY_LEFT_X, PIN_JOY_LEFT_Y, PIN_JOY_LEFT_SW, true);
Joystick joyRight(PIN_JOY_RIGHT_X, PIN_JOY_RIGHT_Y, PIN_JOY_RIGHT_SW, false);

void setup() {
  lcd.begin(16, 2);
  wrapLCD.lcdInitialization(lcd);

  Serial.begin(115200);
  Serial.println("Remote controller started");

  wrapRadio.init();
  joyLeft.init();
  joyRight.init();
}

void loop() {
  extra.flash(TIME_FLASH_MS); // heart beat
  extra.getVoltRc(TIME_VOLTAGE_MS);

  extra.showVoltQuad(lcd, TIME_VOLT_LCD_MS, wrapRadio.ack_msg[0]);
  extra.showVoltRemContrl(lcd, TIME_VOLT_LCD_MS);

  joyLeft.readData(wrapRadio.msg_data[0], wrapRadio.msg_data[1], wrapRadio.msg_data[2], TIME_READ_JOY_MS);
  joyRight.readData(wrapRadio.msg_data[3], wrapRadio.msg_data[4], wrapRadio.msg_data[5], TIME_READ_JOY_MS);

  joyLeft.onLcd(lcd, wrapRadio.msg_data[0], wrapRadio.msg_data[1], wrapRadio.msg_data[2], TIME_READ_JOY_MS);
  joyRight.onLcd(lcd, wrapRadio.msg_data[3], wrapRadio.msg_data[4], wrapRadio.msg_data[5], TIME_READ_JOY_MS);

  wrapRadio.sendTimer(TIME_SEND_DATA_MS);

  wrapLCD.analyzeACK(lcd, wrapRadio.ack_msg, TIME_POWER_WARN_MS);
  wrapLCD.connQuality(lcd, wrapRadio.isConnQualReady, wrapRadio.connQualPerc, TIME_CONN_LCD_MS);
}
