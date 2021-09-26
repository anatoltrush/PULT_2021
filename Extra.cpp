#include "Extra.h"

Extra::Extra(uint8_t led_pin, uint8_t volt_pin):
  flashPin(led_pin), voltPin(volt_pin) {
  pinMode(flashPin, OUTPUT);
  pinMode(voltPin, INPUT);
}

void Extra::flash(uint32_t ms) {
  if (millis() - prev_ms_flash >= ms) {
#ifdef DEBUG_EXTRA
    Serial.print(millis() - prev_ms_flash);
    Serial.print("_");
    Serial.println(__func__);
#endif
    prev_ms_flash = millis();
    //_________________________
    (ledState == LOW) ? ledState = HIGH : ledState = LOW;

    digitalWrite(flashPin, ledState);
  }
}

void Extra::getVolt(uint32_t ms) {
  if (millis() - prev_ms_volt >= ms) {
#ifdef DEBUG_EXTRA
    Serial.print(millis() - prev_ms_volt);
    Serial.print("_");
    Serial.println(__func__);
#endif
    prev_ms_volt = millis();
    //_________________________
    signal = (analogRead(voltPin) / 1024.0f) * MAX_INP_VOLT;
    float div_koeff = RESIST_2 / (RESIST_1 + RESIST_2); // = 0.375
    output = signal / div_koeff;

    // in percs
    float diff_max_min = MAX_VOLT - LOW_VOLT;
    float diff_curr = output - LOW_VOLT;
    percent = (diff_curr / diff_max_min) * 100;
  }
  // TODO: remake algorithm
}
