#ifndef __HANGAR_TASK__
#define __HANGAR_TASK__

#include "devices/Light.h"
#include "devices/PresenceSensor.h"
#include "devices/ProximitySensor.h"
#include "kernel/Task.h"

class HangarTask: public Task {

public:
    HangarTask(PresenceSensor* presenceSensor, ProximitySensor* proximitySensor, Light* light);

    void tick();

private:
    void droneInside();
    void droneTakingOff();
    void droneLanding();
    void droneOutside();
    
    bool isLandingDistanceThresholdReached();
    bool isTakingOffDistanceThresholdReached();
    bool isTimerStarted();
    bool isTimerDone(long timeLimit);
    void startTimer();
    void resetTimer();

private:
    PresenceSensor* presenceSensor;
    ProximitySensor* proximitySensor;
    Light* light;
    long timerTs;
};

#endif

