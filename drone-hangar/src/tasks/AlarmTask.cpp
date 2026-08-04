#include "AlarmTask.h"

#include "model/Context.h"
#include "config.h"

constexpr long TIMER_NOT_STARTED = -1;

AlarmTask::AlarmTask(Button* resetButton, TempSensor* tempSensor)
    : resetButton(resetButton), tempSensor(tempSensor), timerTs(TIMER_NOT_STARTED)
{
}

void AlarmTask::tick() {
    if (Context::isAlarmOff()) {
        if (isPreAlarmTemperatureThresholdReached()) {
            if (!isTimerStarted()) {
                startTimer();
            }
        } else {
            resetTimer();
            Context::resetAlarm();
        }
        if (isTimerDone(T3)) {
            resetTimer();
            Context::setPreAlarm();
        }
    } else if (Context::isPreAlarmOn()) {
        if (isAlarmTemperatureThresholdReached() && !isTimerStarted()) {
            startTimer();
        }
        if (!isPreAlarmTemperatureThresholdReached()) {
            resetTimer();
            Context::resetAlarm();
        }
        if (isTimerDone(T4)) {
            resetTimer();
            Context::setAlarm();
        }
    } else if (Context::isAlarmOn()) {
        if (resetButton->isPressed() && !isPreAlarmTemperatureThresholdReached()) {
            Context::resetAlarm();
        }
    }
}

void AlarmTask::startTimerAtThresholdReached() {
}

bool AlarmTask::isPreAlarmTemperatureThresholdReached() {
    float temperature = tempSensor->getTemperature();
    return temperature >= TEMP1;
}

bool AlarmTask::isAlarmTemperatureThresholdReached() {
    float temperature = tempSensor->getTemperature();
    return temperature >= TEMP2;
}

bool AlarmTask::isTimerStarted() {
    return timerTs != TIMER_NOT_STARTED;
}

bool AlarmTask::isTimerDone(long timeLimit) {
    long timeElapsed = millis() - timerTs;
    return isTimerStarted() && timeElapsed > timeLimit * 1000;
}

void AlarmTask::startTimer() {
    timerTs = millis();
}

void AlarmTask::resetTimer() {
    timerTs = TIMER_NOT_STARTED;
}
