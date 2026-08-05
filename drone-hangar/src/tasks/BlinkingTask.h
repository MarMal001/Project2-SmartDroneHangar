#ifndef __BLINKING_TASK__
#define __BLINKING_TASK__

#include "kernel/Task.h"
#include "model/Context.h"
#include "devices/Light.h"
#include <Arduino.h>

class BlinkingTask: public Task {

public:
  BlinkingTask(Light* pLed, Context* pContext); 
  void tick();

private:  
  void setState(int state);
  long elapsedTimeInState();
  void log(const String& msg);
  
  bool checkAndSetJustEntered();
  
  enum { IDLE, OFF, ON } state;
  long stateTimestamp;
  bool justEntered;

  Light* pLed;
  Context* pContext;
};

#endif