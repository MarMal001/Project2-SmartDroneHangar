#include "ServoMotorImpl.h"
#include <Arduino.h>

constexpr int MAX_ANGLE = 180;
// valori adattati al motore utilizzato
constexpr int MIN = 500;
constexpr int MAX = 2400;
constexpr float COEFF = (MAX - MIN) / (float)MAX_ANGLE;

ServoMotorImpl::ServoMotorImpl(int pin) {
    this->pin = pin;
    _on = false;
}

void ServoMotorImpl::on() {
    motor.attach(pin);
    _on = true;
}

bool ServoMotorImpl::isOn() { return _on; }

void ServoMotorImpl::setPosition(int angle) {
    if (angle > MAX_ANGLE) {
        angle = MAX_ANGLE;
    } else if (angle < 0) {
        angle = 0;
    }
    motor.write(MIN + angle * COEFF);
}

int ServoMotorImpl::getPosition() {
    return (motor.read() - MIN) / COEFF;
}

void ServoMotorImpl::off() {
    _on = false;
    motor.detach();
}
