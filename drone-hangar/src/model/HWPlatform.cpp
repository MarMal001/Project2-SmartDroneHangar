#include "HWPlatform.h"
#include <Arduino.h>
#include "devices/ButtonImpl.h"
#include "config.h"
#include "devices/Led.h"
#include "Servo.h"
#include "kernel/Logger.h"

#define MAX_TIME ((long) 25000)

void wakeUp() {}

HWPlatform::HWPlatform()
{
	pButton = new ButtonImpl(BT_PIN);
	pMotor = new Servo();
	pMotor->attach(MOTOR_PIN);
	
	for (int i = 0; i < NUMBER_LEDS; i++) {
		pLeds[i] = new Led(ledPins[i]);
	}

	pPir = new Pir(PIR_PIN);
	pSonar = new Sonar(ECHO_PIN, TRIG_PIN, MAX_TIME);
	pTempSensorNTC = new TempSensorNTC(TEMP_PIN);

}

void HWPlatform::init()
{
}

Button *HWPlatform::getButton()
{
	return this->pButton;
}

Led *HWPlatform::getLed(int index)
{
	return this->pLeds[index];
}

Servo *HWPlatform::getMotor()
{
	return this->pMotor;
}

Pir *HWPlatform::getPir()
{
	return this->pPir;
}

Sonar *HWPlatform::getSonar()
{
	return this->pSonar;
}

TempSensorNTC *HWPlatform::getTempSensorNTC()
{
	return this->pTempSensorNTC;
}
