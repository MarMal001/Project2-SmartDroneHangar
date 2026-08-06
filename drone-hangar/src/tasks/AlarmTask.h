#ifndef __ALARM_TASK__
#define __ALARM_TASK__

#include "devices/Button.h"
#include "devices/Light.h"
#include "devices/TempSensor.h"
#include "kernel/Task.h"

class AlarmTask: public Task {

public:
    AlarmTask(Button* resetButton, TempSensor* tempSensor, Light* alarmLight);

    void tick();

private:
    void alarmOff();
    void preAlarmOn();
    void alarmOn();

    void startTimerAtThresholdReached();
    bool isPreAlarmTemperatureThresholdReached();
    bool isAlarmTemperatureThresholdReached();
    bool isTimerStarted();
    bool isTimerDone(long timeLimit);
    void startTimer();
    void resetTimer();

private:
    Button* resetButton;
    TempSensor* tempSensor;
    Light* alarmLight;
    long timerTs;
};

#endif
