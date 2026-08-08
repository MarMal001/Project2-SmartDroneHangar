#ifndef __CONTEXT__
#define __CONTEXT__

enum HangarState {
    DRONE_INSIDE,
    DRONE_TAKE_OFF,
    DRONE_OUTSIDE,
    DRONE_LANDING
};

enum AlarmState {
    NO_ALARM,
    PRE_ALARM,
    ALARM
};

class Context {

public:
    static void setHangarState(HangarState state);

    static bool isDroneInside();
    static bool isDroneOutside();
    static bool isDroneLanding();
    static bool isDroneTakingOff();

    static void setAlarm();
    static void setPreAlarm();
    static void resetAlarm();

    static bool isAlarmOff();
    static bool isPreAlarmOn();
    static bool isAlarmOn();

    static float getDistanceFromDrone();
    static void setDistanceFromDrone(float distance);

    static bool isHangarDoorOpen();
    static bool isRequestedDoorOpening();
    static void openHangarDoor();
    static void setHangarDoorOpen();
    static void setHangarDoorClosed();

    static Context& getInstance();

private:
    Context();

private:
    HangarState hangarState;
    AlarmState alarmState;
    float distanceFromDrone;
    bool hangarDoorOpen;
    bool requestHangarDoorOpening;
};

#endif
