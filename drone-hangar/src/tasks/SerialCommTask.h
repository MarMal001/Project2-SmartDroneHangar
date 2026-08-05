#ifndef __SERIAL_COMM_TASK__
#define __SERIAL_COMM_TASK__

#include "kernel/Task.h"

class SerialCommTask: public Task {

public:
    SerialCommTask();

    void tick();

private:
    void handleIncomingCommands();
    void sendCurrentState();
    void handleOutgoingAlarm();

    const char* droneStateToString();
    const char* hangarStateToString();

    // true se ha gia mandato "al:ALARM";
    // torna false dopo RESET.
    bool alarmAlreadySent;
};

#endif