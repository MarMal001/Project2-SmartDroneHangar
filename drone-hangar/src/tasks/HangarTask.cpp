#include "tasks/HangarTask.h"
#include <Arduino.h>
#include "devices/PresenceSensor.h"
#include "devices/ProximitySensor.h"
#include "model/Context.h"
#include "config.h"

constexpr long TIMER_NOT_STARTED = -1;

HangarTask::HangarTask(PresenceSensor* presenceSensor, ProximitySensor* proximitySensor, Light* light)
    : presenceSensor(presenceSensor), proximitySensor(proximitySensor), light(light)
{
    Context::setHangarState(DRONE_INSIDE);
}

void HangarTask::tick() {
    if (Context::isDroneInside()) {
        if (!Context::isAlarmOn() && !Context::isPreAlarmOn()) {
            droneInside();
        }
    } else if (Context::isDroneTakingOff()) {
        droneTakingOff();
    } else if (Context::isDroneOutside()) {
        if (!Context::isAlarmOn() && !Context::isPreAlarmOn()) {
            droneOutside();
        }
    } else if (Context::isDroneLanding()) {
        droneLanding();
    }
}

void HangarTask::droneInside() {
    light->switchOn();
    if (Context::isRequestedDoorOpening()) {
        Context::setHangarState(DRONE_TAKE_OFF);
        light->switchOff();
    }
}

void HangarTask::droneTakingOff() {
    Context::setDistanceFromDrone(proximitySensor->getDistance());
    if (isTakingOffDistanceThresholdReached()) {
        if (!isTimerStarted()) {
            startTimer();
        }
    } else {
        resetTimer();
    }
    if (isTimerDone(T1)) {
        resetTimer();
        Context::setHangarState(DRONE_OUTSIDE);
    }
}

void HangarTask::droneLanding() {
    Context::setDistanceFromDrone(proximitySensor->getDistance());
    if (isLandingDistanceThresholdReached()) {
        if (!isTimerStarted()) {
            startTimer();
        }
    } else {
        resetTimer();
    }
    if (isTimerDone(T2)) {
        resetTimer();
        Context::setHangarState(DRONE_INSIDE);
    }
}

void HangarTask::droneOutside() {
    if (Context::isRequestedDoorOpening() && presenceSensor->isDetected()) {
        Context::setHangarState(DRONE_LANDING);
    }
}

bool HangarTask::isLandingDistanceThresholdReached() {
    return Context::getDistanceFromDrone() <= D2;
}

bool HangarTask::isTakingOffDistanceThresholdReached() {
    return Context::getDistanceFromDrone() >= D1;
}

bool HangarTask::isTimerStarted() {
    return timerTs != TIMER_NOT_STARTED;
}

bool HangarTask::isTimerDone(long timeLimit) {
    long timeElapsed = millis() - timerTs;
    return isTimerStarted() && timeElapsed > timeLimit * 1000;
}

void HangarTask::startTimer() {
    timerTs = millis();
}

void HangarTask::resetTimer() {
    timerTs = TIMER_NOT_STARTED;
}
