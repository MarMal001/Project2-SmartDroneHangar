#include "Logger.h"
#include "Protocol.h"
#include "config.h"

void LoggerService::init(unsigned long baudRate) {
    Serial.begin(baudRate);
}

void LoggerService::log(const String& msg) {
    DEBUG_CALL(Serial.println(String(LOG_PREFIX) + msg));
}