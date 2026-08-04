#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "config.h"
#include "devices/Button.h"
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/TempSensorNTC.h"
#include "Servo.h"

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

private:
  Button* pButton;
  Led* pLeds[NUMBER_LEDS];
  Servo* pMotor;
  Pir* pPir;
  Sonar* pSonar;
  TempSensorNTC* pTempSensorNTC;
  
};

#endif