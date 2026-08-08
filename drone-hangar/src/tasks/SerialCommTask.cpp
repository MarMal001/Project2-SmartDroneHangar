#include "SerialCommTask.h"
#include "kernel/SerialComm.h"
#include "kernel/Protocol.h"
#include "model/Context.h"

SerialCommTask::SerialCommTask() : alarmAlreadySent(false), preAlarmAlreadySent(false)
{
}

void SerialCommTask::tick()
{
    handleIncomingCommands();
    sendCurrentState();
    handleOutgoingAlarm();
}

void SerialCommTask::handleIncomingCommands()
{
    SerialCommService::poll();

    if (SerialCommService::isOpenCommandPending())
    {
        SerialCommService::consumeOpenCommand();
        Context::openHangarDoor();
    }
}

void SerialCommTask::sendCurrentState()
{
    float distanceM = Context::getDistanceFromDrone();

    int distanceCm = (distanceM < 0) ? -1 : (int)(distanceM * 100.0f + 0.5f); // +0.5 per arrotondare
    SerialCommService::sendState(droneStateToString(), hangarStateToString(), distanceCm);
}

void SerialCommTask::handleOutgoingAlarm()
{
    if (Context::isAlarmOn() && !Context::isDroneInside())
    {
        if (!alarmAlreadySent)
        {
            SerialCommService::sendAlarm();
            alarmAlreadySent = true;
        }
    }
    else if (Context::isAlarmOff())
    {
        alarmAlreadySent = false;
    }
}

void SerialCommTask::handleOutgoingPreAlarm()
{
    if (Context::isPreAlarmOn())
    {
        if (!preAlarmAlreadySent)
        {
            SerialCommService::sendPreAlarm();
            preAlarmAlreadySent = true;
        }
    }
    else
    {
        preAlarmAlreadySent = false;
    }
}

const char *SerialCommTask::droneStateToString()
{
    if (Context::isDroneInside())
        return MSG_DRONE_REST;
    if (Context::isDroneTakingOff())
        return MSG_DRONE_TAKEOFF;
    if (Context::isDroneOutside())
        return MSG_DRONE_OUT;
    return MSG_DRONE_LANDING;
}

const char *SerialCommTask::hangarStateToString()
{
    if (Context::isAlarmOff())
        return MSG_HANGAR_NORMAL;
    if (Context::isPreAlarmOn())
        return MSG_HANGAR_PREALARM;
    return MSG_HANGAR_ALARM;
}