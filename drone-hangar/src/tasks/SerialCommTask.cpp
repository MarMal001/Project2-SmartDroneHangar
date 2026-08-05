#include "SerialCommTask.h"
#include "kernel/SerialComm.h"
#include "kernel/Protocol.h"
#include "model/Context.h"

SerialCommTask::SerialCommTask(): alarmAlreadySent(false){

}

void SerialCommTask::tick() {
    handleIncomingCommands();
    sendCurrentState();
    handleOutgoingAlarm();
}

void SerialCommTask::handleIncomingCommands() {
    SerialCommService::poll();

    if (SerialCommService::isOpenCommandPending()) {
        SerialCommService::consumeOpenCommand();
        Context::openHangarDoor();
    }
}

void SerialCommTask::sendCurrentState() {
    int distanceCm = (int) Context::getDistanceFromDrone();
    SerialCommService::sendState(droneStateToString(), hangarStateToString(), distanceCm);
}

void SerialCommTask::handleOutgoingAlarm() {
    if (Context::isAlarmOn() && Context::isDroneOutside()) {
        if (!alarmAlreadySent) {
            SerialCommService::sendAlarm();
            alarmAlreadySent = true;
        }
    } else if (Context::isAlarmOff()) {
        alarmAlreadySent = false;
    }
}

const char* SerialCommTask::droneStateToString() {
    if (Context::isDroneInside())    return MSG_DRONE_REST;
    if (Context::isDroneTakingOut()) return MSG_DRONE_TAKEOFF;
    if (Context::isDroneOutside())   return MSG_DRONE_OUT;
    return MSG_DRONE_LANDING;
}

const char* SerialCommTask::hangarStateToString() {
    if (Context::isAlarmOff())   return MSG_HANGAR_NORMAL;
    if (Context::isPreAlarmOn()) return MSG_HANGAR_PREALARM;
    return MSG_HANGAR_ALARM;
}