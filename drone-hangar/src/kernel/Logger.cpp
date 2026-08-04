#include "Logger.h"
#include "Protocol.h"

void LoggerService::init(unsigned long baudRate) {
    Serial.begin(baudRate);
}

void LoggerService::log(const String& msg) {
    Serial.println(String(LOG_PREFIX) + msg);
}