#include "SerialComm.h"
#include "Logger.h"
#include "Protocol.h"

SerialCommService::SerialCommService()
{
    inputBuffer = "";
    inputBuffer.reserve(32);
    openCommandPending = false;
}

void SerialCommService::poll()
{
    while (Serial.available() > 0)
    {
        char c = (char)Serial.read();
        if (c == '\n')
        {
            processMessage(getInstance().inputBuffer);
            getInstance().inputBuffer = "";
        }
        else if (c != '\r')
        {
            getInstance().inputBuffer += c;
        }
    }
}

void SerialCommService::processMessage(const String &msg)
{
    if (msg == CMD_OPEN)
    {
        getInstance().openCommandPending = true;
    }
    else if (msg.length() > 0)
    {
        LoggerService::log("unknown cmd: " + msg);
    }
}

bool SerialCommService::isOpenCommandPending()
{
    return getInstance().openCommandPending;
}

void SerialCommService::consumeOpenCommand()
{
    getInstance().openCommandPending = false;
}

void SerialCommService::sendState(const String &droneState, const String &hangarState, int distanceCm)
{
    Serial.print(STATE_PREFIX);
    Serial.print(droneState);
    Serial.print(":");
    Serial.print(hangarState);
    Serial.print(":");
    Serial.println(distanceCm);
}

void SerialCommService::sendAlarm()
{
    Serial.print(ALARM_PREFIX);
    Serial.println(MSG_HANGAR_ALARM);
}

void SerialCommService::sendPreAlarm()
{
    Serial.print(ALARM_PREFIX);
    Serial.println(MSG_HANGAR_PREALARM);
}

SerialCommService& SerialCommService::getInstance() {
    static SerialCommService instance;
    return instance;
}