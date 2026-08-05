#ifndef __BLINKING_TASK__
#define __BLINKING_TASK__

#include "kernel/Task.h"
#include "devices/Light.h"
#include <Arduino.h>

class BlinkingTask: public Task {

public:
    BlinkingTask(Light* pLight); 
    void tick();

private:  
    enum LightState { 
        IDLE,
        OFF,
        ON
    };

    void setState(LightState state);
    long elapsedTimeInState();
    void log(const String& msg);

    bool checkAndSetJustEntered();

    long stateTimestamp;
    bool justEntered;
    LightState state;

    Light* pLight;
};

#endif
