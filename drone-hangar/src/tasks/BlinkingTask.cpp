#include "tasks/BlinkingTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

BlinkingTask::BlinkingTask(Light* pLed): 
    pLed(pLed){
    setState(IDLE);
}
  
void BlinkingTask::tick(){
    switch (state){   
        case IDLE: {
            if (this->checkAndSetJustEntered()){
                pLed->switchOff();
                Logger.log(F("[BT] IDLE"));

            }
            if (Contex::isDroneTakingOff() || Contex::isDroneLanding()){
                setState(OFF);
            }
            break;
        }
        case OFF: {
            if (this->checkAndSetJustEntered()){
                pLed->switchOff();
                Logger.log(F("[BT] OFF"));
            }
            if (Context::isDroneOutside() || Context::isDroneInside()){
                setState(IDLE);
            } else {
                setState(ON);
            }
            break;
        }
        case ON: {
            if (this->checkAndSetJustEntered()){
                pLed->switchOn();
                Logger.log(F("[BT] ON"));
            }
            if (Context::isDroneOutside() || Context::isDroneInside()){
                setState(IDLE);
            } else {
                setState(OFF);
            }
            break;
        }
    }
}


void BlinkingTask::setState(int s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long BlinkingTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool BlinkingTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}