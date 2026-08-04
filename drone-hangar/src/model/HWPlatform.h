#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "config.h"
#include "devices/Button.h"
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/TempSensorNTC.h"
#include "Servo.h"
#include "LiquidCrystal_I2C.h"

class HWPlatform {

public:
    HWPlatform();
    void init();

    Button* getButton();
    Led*  getLed(int index);
    Servo* getMotor();
    Pir*  getPir();
    Sonar* getSonar();
    TempSensorNTC* getTempSensorNTC();
    LiquidCrystal_I2C* getLCD();

private:
    Button* pButton;
    Led* pLeds[NUMBER_LEDS];
    Servo* pMotor;
    Pir* pPir;
    Sonar* pSonar;
    TempSensorNTC* pTempSensorNTC;
    LiquidCrystal_I2C* pLcd;
  
};

#endif