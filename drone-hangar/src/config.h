#ifndef __CONFIG__
#define __CONFIG__

#include <Arduino.h>

constexpr int PIR_PIN        = 2;
constexpr int SONAR_ECHO_PIN = 3;
constexpr int SONAR_TRIG_PIN = 4;
constexpr int BT_PIN         = 6;
constexpr int G_LED1_PIN     = 7;
constexpr int G_LED2_PIN     = 8;
constexpr int ALARM_LED_PIN  = 9;
constexpr int MOTOR_PIN      = 11;
constexpr int TEMP_PIN       = A0;

constexpr long T1 = 3; // Seconds
constexpr long T2 = 3; // Seconds
constexpr long T3 = 3; // Seconds
constexpr long T4 = 1; // Seconds
constexpr float D1 = 0.5; // Meters
constexpr float D2 = 0.05; // Meters
constexpr float TEMP1 = 35.0; // Degrees
constexpr float TEMP2 = 39.0; // Degrees

enum LED {
    ALARM_LED,
    G_LED1,
    G_LED2,
    NUMBER_LEDS
};

constexpr int ledPins[NUMBER_LEDS] = { ALARM_LED_PIN, G_LED1_PIN, G_LED2_PIN };
 
#endif