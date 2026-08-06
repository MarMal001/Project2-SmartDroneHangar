#include "tasks/HangarDoorTask.h"
#include <Arduino.h>
#include "devices/ServoMotor.h"
#include "model/Context.h"

constexpr int MAX_ANGLE_MOTOR = 90;
constexpr int MIN_ANGLE_MOTOR = 0;
constexpr int COMPLETE_MOVEMENT_TIME = 2000; // Milliseconds

HangarDoorTask::HangarDoorTask(ServoMotor* servoMotor) : servoMotor(servoMotor) {
    state = OPEN;
    startMovementTs = 0;
    currentPos = 0;
    servoMotor->on();
}

void HangarDoorTask::tick() {
    long dt = millis() - startMovementTs;
    if (state == CLOSED) {
        Context::setHangarDoorClosed();
        if (Context::isDroneTakingOff() || Context::isDroneLanding()) {
            state = OPENING;
        }
    } else if (state == OPENING) {
        currentPos += (((float) dt)/COMPLETE_MOVEMENT_TIME)*MAX_ANGLE_MOTOR;
        servoMotor->setPosition(currentPos);
        if (servoMotor->getPosition() >= MAX_ANGLE_MOTOR) {
            state = OPEN;
        }
    } else if (state == OPEN) {
        Context::setHangarDoorOpen();
        if (Context::isDroneInside() || Context::isDroneOutside()) {
            state = CLOSING;
        }
    } else if (state == CLOSING) {
        currentPos -= (((float) dt)/COMPLETE_MOVEMENT_TIME)*MAX_ANGLE_MOTOR;
        servoMotor->setPosition(currentPos);
        if (servoMotor->getPosition() <= MIN_ANGLE_MOTOR) {
            state = CLOSED;
        }
    }
    startMovementTs = millis();
}
