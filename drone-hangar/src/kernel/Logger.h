#ifndef __LOGGER__
#define __LOGGER__

#include <Arduino.h>

class LoggerService {
    
public: 
    static void init(unsigned long baudRate);
    static void log(const String& msg); // TODO: alarm log

private:
    static LoggerService instance;
};

#endif