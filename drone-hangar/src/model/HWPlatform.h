#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "config.h"
#include "devices/Button.h"
#include "devices/Light.h"
#include "devices/PresenceSensor.h"
#include "devices/ProximitySensor.h"
#include "devices/TempSensor.h"
#include "Servo.h"
#include "LiquidCrystal_I2C.h"

class HWPlatform {

public:
    HWPlatform();
    void init();

    Button* getButton();
    Light*  getLight(int index);
    Servo* getMotor();
    PresenceSensor*  getPresenceSensor();
    ProximitySensor* getProximitySensor();
    TempSensor* getTempSensor();
    LiquidCrystal_I2C* getLCD();

private:
    Button* pButton;
    Light* pLights[NUMBER_LEDS];
    Servo* pMotor;
    PresenceSensor* pPresenceSensor;
    ProximitySensor* pProximitySensor;
    TempSensor* pTempSensorNTC;
    LiquidCrystal_I2C* pLcd;
  
};

#endif