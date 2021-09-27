#ifndef DEFINES_H
#define DEFINES_H

#include <Arduino.h>

// <----- DIGITAL PINS ----->

#define PIN_LCD_D7      2
#define PIN_LCD_D6      3
#define PIN_LCD_D5      4
#define PIN_LCD_D4      5
#define PIN_LCD_EN      6
#define PIN_LCD_RS      7

#define PIN_FLASH       8

#define PIN_NRF_CE      9
#define PIN_NRF_CS      10
#define PIN_NRF_MOSI    11
#define PIN_NRF_MISO    12
#define PIN_NRF_SCK     13

// <----- ANALOG PINS ----->

#define PIN_VOLT          A2

// JOYSTICKS
#define PIN_JOY_LEFT_X    A0
#define PIN_JOY_LEFT_Y    A1
#define PIN_JOY_LEFT_SW   A5
#define PIN_JOY_RIGHT_X   A3
#define PIN_JOY_RIGHT_Y   A4
#define PIN_JOY_RIGHT_SW  A6

// <----- PERIODS ----->

#define TIME_READ_JOY_MS    20
#define TIME_SEND_DATA_MS   20
#define TIME_FLASH_MS       500
#define TIME_VOLTAGE_MS     2000
#define TIME_POWER_WARN_MS  400
#define TIME_CONN_UPD_MS    2000
#define TIME_CONN_LCD_MS    200

// <----- CONSTANT VALUES ----->

// DATA
#define SIZE_OF_DATA    6
#define SIZE_OF_ACK     3

#define DATA_MIN        0
#define DATA_AVRG       1
#define DATA_MAX        2

// LCD
#define LCD_LEFT_POS    10
#define LCD_RIGHT_POS   13

// RESISTANCE
#define RESIST_1        0.0f
#define RESIST_2        0.0f

// VOLTAGE
#define MAX_INP_VOLT    5.0
#define LOW_VOLT        6.6
#define MAX_VOLT        8.4

#endif // DEFINES_H
