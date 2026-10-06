#include "Context.h"

void Context::setHangarState(HangarState state) {
    getInstance().hangarState = state;
}

bool Context::isDroneInside() {
    return getInstance().hangarState == DRONE_INSIDE;
}

bool Context::isDroneOutside() {
    return getInstance().hangarState == DRONE_OUTSIDE;
}

bool Context::isDroneLanding() {
    return getInstance().hangarState == DRONE_LANDING;
}

bool Context::isDroneTakingOff() {
    return getInstance().hangarState == DRONE_TAKE_OFF;
}

void Context::setAlarm() {
    getInstance().alarmState = ALARM;
}

void Context::setPreAlarm() {
    getInstance().alarmState = PRE_ALARM;
}

void Context::resetAlarm() {
    getInstance().alarmState = NO_ALARM;
}

bool Context::isAlarmOff() {
    return getInstance().alarmState == NO_ALARM;
}

bool Context::isPreAlarmOn() {
    return getInstance().alarmState == PRE_ALARM;
}

bool Context::isAlarmOn() {
    return getInstance().alarmState == ALARM;
}

float Context::getDistanceFromDrone() {
    return getInstance().distanceFromDrone;
}

void Context::setDistanceFromDrone(float distance) {
    getInstance().distanceFromDrone = distance;
}

bool Context::isHangarDoorOpen() {
    return getInstance().hangarDoorOpen;
}

bool Context::isRequestedDoorOpening() {
    return getInstance().requestHangarDoorOpening;
}

void Context::openHangarDoor() {
    getInstance().requestHangarDoorOpening = true;
}

void Context::setHangarDoorOpen() {
    getInstance().requestHangarDoorOpening = false;
    getInstance().hangarDoorOpen = true;
}

void Context::setHangarDoorClosed() {
    getInstance().hangarDoorOpen = false;
}

Context& Context::getInstance() {
    static Context instance;
    return instance;
}

Context::Context()
    : hangarState(DRONE_INSIDE), alarmState(NO_ALARM), distanceFromDrone(0.0), hangarDoorOpen(false), requestHangarDoorOpening(false)
{
}
