#include "Joystick.hpp"

Joystick::Joystick(uint8_t x_p, uint8_t y_p, uint8_t sw_p, bool is_lft) :
  x_pin(x_p), y_pin(y_p),
  sw_pin(sw_p), is_left(is_lft)
{
  pinMode(x_pin, INPUT);
  pinMode(y_pin, INPUT);
  pinMode(sw_pin, INPUT);
}

void Joystick::init() {
  uint8_t dataX = map(analogRead(x_pin), 0, 1023, 255, 0);
  if (dataX != 127)
    differ_x = dataX - 127;

  uint8_t dataY = map(analogRead(y_pin), 0, 1023, 255, 0);
  if (dataY != 127)
    differ_y = dataY - 127;

#ifdef DEBUG_JOY
  is_left ? Serial.print("Left: ") : Serial.print("Right: ");
  Serial.print(" | differ_x:");
  Serial.print(differ_x);
  Serial.print(" | differ_y:");
  Serial.println(differ_y);
  Serial.println("JOYSTICK CALIBRATED!");
#endif // DEBUG_JOY
}

void Joystick::readData(uint8_t& dataX, uint8_t& dataY, uint8_t& dataSW, uint32_t ms) {
  if (millis() - prev_mills_calc >= ms) {

    dataX = map(analogRead(x_pin), 0, 1023, 255, 0);
    if (dataX > (0 + differ_x) && dataX < (255 - differ_x))
      dataX -= differ_x;

    dataY = map(analogRead(y_pin), 0, 1023, 255, 0);
    if (dataY > (0 + differ_y) && dataY < (255 - differ_y))
      dataY -= differ_y;

    dataSW = analogRead(sw_pin);
    dataSW = 255 - dataSW;

#ifdef IS_1_0_DATA
    if (dataX < 90) dataX = DATA_MIN;
    else if (dataX > 170) dataX = DATA_MAX;
    else dataX = DATA_AVRG;

    if (dataY < 90) dataY = DATA_MIN;
    else if (dataY > 170) dataY = DATA_MAX;
    else dataY = DATA_AVRG;

    dataSW = (dataSW > 170) ? DATA_MAX : DATA_MIN;
#endif
#ifdef DEBUG_JOY
    Serial.print(millis() - prev_mills_calc);
    Serial.print("_");
    Serial.print(__func__);
    Serial.print("_");
    is_left ? Serial.print("Left: ") : Serial.print("Right: ");
    Serial.print("sigX:");
    Serial.print(dataX);
    Serial.print(" | sigY:");
    Serial.print(dataY);
    Serial.print(" | sigSW:");
    Serial.print(dataSW);
    Serial.println();
#endif // DEBUG_JOY
    prev_mills_calc = millis();
  }
}

void Joystick::on_lcd(LiquidCrystal& lcd, uint8_t x, uint8_t y, uint8_t sw, uint32_t ms) {
  if (millis() - prev_mills_show >= ms) {
    uint8_t pos = 0;
    if (is_left) pos = LCD_LEFT_POS;
    else pos = LCD_RIGHT_POS;

    // X
    lcd.setCursor(pos, 1);
    if (x > 5 && x < 64) lcd.write("_");
    else if (x >= 64 && x < 128) lcd.write(byte(4));
    else if (x >= 128 && x < 192) lcd.write(byte(5));
    else if (x >= 192 && x <= 255) lcd.write(byte(6));
    else lcd.write(" ");
    // Y
    lcd.setCursor(pos + 1, 1);
    if (y > 5 && y < 64) lcd.write("_");
    else if (y >= 64 && y < 128) lcd.write(byte(4));
    else if (y >= 128 && y < 192) lcd.write(byte(5));
    else if (y >= 192 && y <= 255) lcd.write(byte(6));
    else lcd.write(" ");
    // CLICKED
    lcd.setCursor(pos + 2, 1);
    if (sw >= 128) lcd.write(byte(6));
    else lcd.write("_");

#ifdef IS_1_0_DATA
    // X
    lcd.setCursor(pos, 1);
    if (x == DATA_MIN) lcd.write("_");
    else if (x == DATA_AVRG) lcd.write(byte(4));
    else lcd.write(byte(6));
    // Y
    lcd.setCursor(pos + 1, 1);
    if (y == DATA_MIN) lcd.write("_");
    else if (y == DATA_AVRG) lcd.write(byte(4));
    else lcd.write(byte(6));
    // CLICKED
    lcd.setCursor(pos + 2, 1);
    if (sw >= DATA_AVRG) lcd.write(byte(6));
    else lcd.write("_");
#endif

    prev_mills_show = millis();
  }
}
