#ifndef __CONFIG__
#define __CONFIG__

#include <Arduino.h>

constexpr int PIR_PIN        = 2;
constexpr int SONAR_ECHO_PIN = 3;
constexpr int SONAR_TRIG_PIN = 4;
constexpr int MOTOR_PIN      = 5;
constexpr int BT_PIN         = 6;
constexpr int G_LED1_PIN     = 7;
constexpr int G_LED2_PIN     = 8;
constexpr int ALARM_LED_PIN  = 9;
constexpr int TEMP_PIN       = A0;

enum LED {
    ALARM_LED,
    G_LED1,
    G_LED2,
    NUMBER_LEDS
};

constexpr int ledPins[NUMBER_LEDS] = { ALARM_LED_PIN, G_LED1_PIN, G_LED2_PIN };
 
#endif