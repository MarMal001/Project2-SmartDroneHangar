#ifndef __CONFIG__
#define __CONFIG__

#define BT_PIN  6   
#define MOTOR_PIN   5
#define PIR_PIN     2 
#define TEMP_PIN    A0

enum LED {
    ALARM_LED,
    G_LED1,
    G_LED2,
    NUMBER_LEDS
};

enum SonarPins {
    ECHO_PIN,
    TRIG_PIN,
    NUMBER_SONAR_PINS
};

int ledPins[NUMBER_LEDS] = {9, 7, 8}; 
int sonarPins[NUMBER_SONAR_PINS] = {3, 4};
 
#endif