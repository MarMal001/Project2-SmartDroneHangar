#include "tasks/LCDTask.h"
#include <Arduino.h>
#include "config.h"
#include "model/Context.h"

LCDTask::LCDTask(LiquidCrystal_I2C* lcd) : lcd(lcd) {

}

void LCDTask::tick() {
    String state = "";
    if (Context::isDroneInside()) state = "DRONE INSIDE";
    else if (Context::isDroneOutside()) state = "DRONE OUT";
    else if (Context::isDroneLanding()) state = "LANDING";
    else if (Context::isDroneTakingOff()) state = "TAKE OFF";


    while (state.length() < LCD_COLUMNS) {
        state += ' ';
    }

    if (state == lastDisplayed) {
        return; 
    }

    lcd->setCursor(0, 0);
    lcd->print(state);
    lastDisplayed = state;
}
