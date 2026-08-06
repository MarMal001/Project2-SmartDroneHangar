#ifndef __HANGAR_DOOR_TASK__
#define __HANGAR_DOOR_TASK__

#include "devices/ServoMotor.h"
#include "kernel/Task.h"

class HangarDoorTask: public Task {

public:
    HangarDoorTask(ServoMotor* servoMotor);

    void tick();

private:
    enum DoorState {
        OPEN,
        OPENING,
        CLOSED,
        CLOSING
    };

private:
    ServoMotor* servoMotor;
    DoorState state;
    long startMovementTs;
    float currentPos;
};

#endif
