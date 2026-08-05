#include "SerialComm.h"
#include "Protocol.h"

SerialCommService SerialCommService::instance;

SerialCommService::SerialCommService() {
    inputBuffer = "";
    inputBuffer.reserve(32);
    openCommandPending = false;
}

void SerialCommService::poll() {
    while (Serial.available() > 0){
        char c = (char) Serial.read();
        if (c == '\n'){
            processMessage(instance.inputBuffer);
            instance.inputBuffer = "";
        } else if (c != '\r'){
            instance.inputBuffer += c;
        }
    }
}

void SerialCommService::processMessage(const String& msg) {
    if (msg == CMD_OPEN){
        instance.openCommandPending = true;
    }
    // else Logger.log("unknown: " + msg);
    // decommentare per leggere messaggi malformati che altrimenti ignoriamo
}

bool SerialCommService::isOpenCommandPending() {
    return instance.openCommandPending;
}

void SerialCommService::consumeOpenCommand() {
    instance.openCommandPending = false;
}

void SerialCommService::sendState(const String& droneState, const String& hangarState, int distanceCm) {
    Serial.print(STATE_PREFIX);
    Serial.print(droneState);
    Serial.print(":");
    Serial.print(hangarState);
    Serial.print(":");
    Serial.println(distanceCm);
}

void SerialCommService::sendAlarm() {
    Serial.print(ALARM_PREFIX);
    Serial.println(MSG_HANGAR_ALARM);
}

void SerialCommService::sendPreAlarm() {
    Serial.print(ALARM_PREFIX);
    Serial.println(MSG_HANGAR_PREALARM);
}