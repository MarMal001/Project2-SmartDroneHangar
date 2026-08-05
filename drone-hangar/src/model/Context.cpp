#include "Context.h"

Context Context::instance;

void Context::setHangarState(HangarState state) {
    instance.hangarState = state;
}

bool Context::isDroneInside() {
    return instance.hangarState == DRONE_INSIDE;
}

bool Context::isDroneOutside() {
    return instance.hangarState == DRONE_OUTSIDE;
}

bool Context::isDroneLanding() {
    return instance.hangarState == DRONE_LANDING;
}

bool Context::isDroneTakingOut() {
    return instance.hangarState == DRONE_TAKE_OFF;
}

void Context::setAlarm() {
    instance.alarmState = ALARM;
}

void Context::setPreAlarm() {
    instance.alarmState = PRE_ALARM;
}

void Context::resetAlarm() {
    instance.alarmState = NO_ALARM;
}

bool Context::isAlarmOff() {
    return instance.alarmState == NO_ALARM;
}

bool Context::isPreAlarmOn() {
    return instance.alarmState == PRE_ALARM;
}

bool Context::isAlarmOn() {
    return instance.alarmState == ALARM;
}

bool Context::isDroneDetected() {
    return instance.droneDetected;
}

void Context::setDroneDetected(bool detected) {
    instance.droneDetected = detected;
}

float Context::getDistanceFromDrone() {
    return instance.distanceFromDrone;
}

void Context::setDistanceFromDrone(float distance) {
    instance.distanceFromDrone = distance;
}

bool Context::isHangarDoorOpen() {
    return instance.hangarDoorOpen;
}

void Context::openHangarDoor() {
    instance.requestHangarDoorOpening = true;
}

void Context::setHangarDoorOpen() {
    instance.requestHangarDoorOpening = false;
    instance.hangarDoorOpen = true;
}

Context::Context()
    : hangarState(DRONE_INSIDE), alarmState(NO_ALARM), distanceFromDrone(0.0), droneDetected(false), hangarDoorOpen(false), requestHangarDoorOpening(false)
{
}