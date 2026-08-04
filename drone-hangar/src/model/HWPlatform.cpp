#include "HWPlatform.h"
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "devices/ButtonImpl.h"
#include "config.h"
#include "devices/Led.h"
#include "Servo.h"

constexpr long MAX_TIME = 25000L; //This time is used to determine the max distance detected by the sonar -> 25000ms ~ 4 meters

void wakeUp() {}

HWPlatform::HWPlatform() {
	pButton = new ButtonImpl(BT_PIN);
	pLcd = new LiquidCrystal_I2C(0x27, 20, 4);
	pLcd->init();
	pLcd->backlight();
	pMotor = new Servo();
	pMotor->attach(MOTOR_PIN);
	
	for (int i = 0; i < NUMBER_LEDS; i++) {
		pLeds[i] = new Led(ledPins[i]);
	}

	pPir = new Pir(PIR_PIN);
	pSonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, MAX_TIME);
	pTempSensorNTC = new TempSensorNTC(TEMP_PIN);
}

void HWPlatform::init() {
}

Button *HWPlatform::getButton() {
	return this->pButton;
}

Led *HWPlatform::getLed(int index) {
	return this->pLeds[index];
}

Servo *HWPlatform::getMotor() {
	return this->pMotor;
}

Pir *HWPlatform::getPir() {
	return this->pPir;
}

Sonar *HWPlatform::getSonar() {
	return this->pSonar;
}

TempSensorNTC *HWPlatform::getTempSensorNTC() {
	return this->pTempSensorNTC;
}

LiquidCrystal_I2C *HWPlatform::getLCD() {
	return this->pLcd;
}