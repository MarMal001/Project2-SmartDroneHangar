#include "config.h"
#include "kernel/Logger.h"
#include "kernel/Scheduler.h"
#include "model/HWPlatform.h"
#include "tasks/AlarmTask.h"
#include <Arduino.h>

HWPlatform* hw;
Scheduler* scheduler;

void setup() {
    LoggerService::init(9600);
    hw = new HWPlatform();
    scheduler = new Scheduler();
    scheduler->init(50);

    Task* alarmTask = new AlarmTask(hw->getButton(), hw->getTempSensor(), hw->getLight(ALARM_LED));
    alarmTask->init(50);

    scheduler->addTask(alarmTask);
}

void loop() {
    scheduler->schedule();
}
