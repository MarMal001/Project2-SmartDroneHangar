#include "tasks/BlinkingTask.h"
#include "model/Context.h"
#include <Arduino.h>

BlinkingTask::BlinkingTask(Light* pLight): 
    pLight(pLight){
    setState(IDLE);
}
  
void BlinkingTask::tick(){
    switch (state){   
        case IDLE: {
            if (this->checkAndSetJustEntered()){
                pLight->switchOff();
            }
            if (Context::isDroneTakingOff() || Context::isDroneLanding()){
                setState(OFF);
            }
            break;
        }
        case OFF: {
            if (this->checkAndSetJustEntered()){
                pLight->switchOff();
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
                pLight->switchOn();
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


void BlinkingTask::setState(LightState s){
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
