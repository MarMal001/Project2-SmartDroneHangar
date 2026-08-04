#ifndef __LOGGER__
#define __LOGGER__

#include "Arduino.h"


class LoggerService {
    
public: 
  void init(unsigned long baudRate);
  
  void log(const String& msg);
};

extern LoggerService Logger;

#endif