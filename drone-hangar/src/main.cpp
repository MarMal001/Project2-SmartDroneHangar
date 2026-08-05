#include "config.h"
#include "kernel/Logger.h"
#include "kernel/Scheduler.h"
#include "model/HWPlatform.h"
#include "tasks/AlarmTask.h"
#include "tasks/LCDTask.h"
#include "tasks/SerialCommTask.h"
#include "tasks/BlinkingTask.h"
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

    Task* serialCommTask = new SerialCommTask();
    serialCommTask->init(50);
    scheduler->addTask(serialCommTask);

    Task* blinkingTask = new BlinkingTask(hw->getLight(G_LED2_PIN));
    blinkingTask->init(500);
    scheduler->addTask(blinkingTask);

    Task* lcdTask = new LCDTask(hw->getLCD());
    lcdTask->init(200);
    scheduler->addTask(lcdTask);
}

void loop() {
    scheduler->schedule();
}
